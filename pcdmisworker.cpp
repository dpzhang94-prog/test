#include "pcdmisworker.h"

#include <QAxObject>
#include <QTimer>
#include <QVariant>

#include <oaidl.h>
#include <objbase.h>

namespace {
constexpr auto kPcdmisProgId = "PCDLRN.Application";
constexpr int kFailureLimit = 3;
constexpr int kReflectorNotFoundErrorType = 2;
constexpr int kIdenticalCoordinateLimit = 10;
constexpr qint64 kReadoutLossTimeoutMs = 1000;
constexpr qint64 kReadoutStartupWarningMs = 3000;

bool comVariantToInt(const VARIANTARG &argument, int &value)
{
    switch (argument.vt) {
    case VT_I1:
        value = argument.cVal;
        return true;
    case VT_UI1:
        value = argument.bVal;
        return true;
    case VT_I2:
        value = argument.iVal;
        return true;
    case VT_UI2:
        value = argument.uiVal;
        return true;
    case VT_I4:
    case VT_INT:
        value = argument.lVal;
        return true;
    case VT_UI4:
    case VT_UINT:
        value = static_cast<int>(argument.ulVal);
        return true;
    case VT_I2 | VT_BYREF:
        if (argument.piVal != nullptr) {
            value = *argument.piVal;
            return true;
        }
        break;
    case VT_I4 | VT_BYREF:
    case VT_INT | VT_BYREF:
        if (argument.plVal != nullptr) {
            value = *argument.plVal;
            return true;
        }
        break;
    case VT_VARIANT | VT_BYREF:
        if (argument.pvarVal != nullptr) {
            return comVariantToInt(*argument.pvarVal, value);
        }
        break;
    default:
        break;
    }
    return false;
}

QString comVariantToString(const VARIANTARG &argument)
{
    if (argument.vt == VT_BSTR && argument.bstrVal != nullptr) {
        return QString::fromWCharArray(
            argument.bstrVal,
            static_cast<qsizetype>(SysStringLen(argument.bstrVal)));
    }
    if (argument.vt == (VT_BSTR | VT_BYREF) &&
        argument.pbstrVal != nullptr && *argument.pbstrVal != nullptr) {
        return QString::fromWCharArray(
            *argument.pbstrVal,
            static_cast<qsizetype>(SysStringLen(*argument.pbstrVal)));
    }
    if (argument.vt == (VT_VARIANT | VT_BYREF) &&
        argument.pvarVal != nullptr) {
        return comVariantToString(*argument.pvarVal);
    }
    return QString();
}
}

PcdmisWorker::PcdmisWorker(QObject *parent)
    : QObject(parent)
{
}

PcdmisWorker::~PcdmisWorker()
{
    releaseComObjects();
}

void PcdmisWorker::initialize()
{
    // PC-DMIS Automation 使用 COM。工作线程需要独立初始化为 STA，
    // 这样 QAxObject 的调用和 ErrorMsg 事件都由同一线程处理。
    const HRESULT result =
        CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (SUCCEEDED(result)) {
        m_comInitialized = true;
    } else {
        emit errorOccurred(QStringLiteral(
            "PC-DMIS 工作线程初始化 COM 失败（HRESULT=0x%1）。")
                               .arg(static_cast<quint32>(result),
                                    8, 16, QLatin1Char('0')));
    }

    // 定时器同样必须在工作线程启动后创建，确保 timeout 和 COM 调用
    // 始终在同一个线程中执行。
    if (m_pollTimer != nullptr) {
        return;
    }

    m_pollTimer = new QTimer(this);
    m_pollTimer->setInterval(m_pollingIntervalMs);
    m_pollTimer->setTimerType(Qt::PreciseTimer);
    connect(m_pollTimer, &QTimer::timeout,
            this, &PcdmisWorker::pollProbePosition);
}

bool PcdmisWorker::isConnected() const
{
    return m_application != nullptr && m_machine != nullptr;
}

bool PcdmisWorker::isPolling() const
{
    return m_pollTimer != nullptr && m_pollTimer->isActive();
}

void PcdmisWorker::refreshAlignedTrackerOrigin()
{
    if (!isConnected()) {
        emit trackerOriginRefreshFinished(
            false, 0.0, 0.0, 0.0, QStringLiteral("请先连接 PC-DMIS。"));
        return;
    }

    if (!refreshAlignmentMatrix(true)) {
        emit trackerOriginRefreshFinished(
            false, 0.0, 0.0, 0.0,
            QStringLiteral(
                "无法读取当前活动对齐矩阵，请确认 PC-DMIS 中已经建立并激活坐标系。"));
        return;
    }

    emit trackerOriginRefreshFinished(
        true,
        m_alignedTrackerOrigin[0],
        m_alignedTrackerOrigin[1],
        m_alignedTrackerOrigin[2],
        QString());
}

void PcdmisWorker::connectToPcdmis(bool makeVisible)
{
    if (!m_comInitialized) {
        emit errorOccurred(QStringLiteral(
            "PC-DMIS 工作线程的 COM 尚未成功初始化，无法建立连接。"));
        emit connectedChanged(false);
        return;
    }

    if (isConnected()) {
        emit logMessage(QStringLiteral("已经连接到 PC-DMIS。"));
        return;
    }

    releaseComObjects();
    emit logMessage(QStringLiteral("正在创建 COM 对象 PCDLRN.Application ..."));

    m_application = new QAxObject(this);
    if (!m_application->setControl(QString::fromLatin1(kPcdmisProgId)) ||
        m_application->isNull()) {
        const QString message = QStringLiteral(
            "无法创建 PCDLRN.Application。请确认 PC-DMIS 已安装、已授权，"
            "并且 COM 服务已正确注册。");
        releaseComObjects();
        emit errorOccurred(message);
        emit connectedChanged(false);
        return;
    }

    if (makeVisible) {
        m_application->setProperty("Visible", true);
    }

    m_machines = m_application->querySubObject("Machines");
    if (m_machines == nullptr || m_machines->isNull()) {
        const QString message = QStringLiteral(
            "已打开 PC-DMIS，但没有取得 Machines 集合。请确认当前版本支持 Automation 接口。");
        releaseComObjects();
        emit errorOccurred(message);
        emit connectedChanged(false);
        return;
    }

    m_machine = selectMachine(m_machines);
    if (m_machine == nullptr || m_machine->isNull()) {
        const QString message = QStringLiteral(
            "没有取得第一个 Machine 对象。请先在 PC-DMIS 中配置并连接激光跟踪仪。"
            "如果当前 PC-DMIS 的 Machines 集合从 0 开始编号，可在 pcdmisworker.cpp 中调整索引。");
        releaseComObjects();
        emit errorOccurred(message);
        emit connectedChanged(false);
        return;
    }

    // ErrorMsg 并不保证在动态测头读数变红时触发。ReadoutExt 才是帮助
    // 文档所述的“与 XYZ 显示匹配”的控制器读数事件，因此同时监听
    // ReadoutExt 心跳和 ErrorMsg。具体 ReadoutExt 信号用于常见类型库，
    // 通用 COM 事件信号用于类型签名没有完整公开的版本。
    const QMetaObject::Connection machineEventConnection =
        connect(m_machine, &QAxObject::signal,
                this, &PcdmisWorker::onMachineEvent,
                Qt::DirectConnection);
    const QMetaObject::Connection readoutConnection =
        connect(m_machine, SIGNAL(ReadoutExt(double,double,double)),
                this, SLOT(onMachineReadoutExt(double,double,double)),
                Qt::DirectConnection);

    m_reflectorState = ReflectorState::Unknown;
    m_readoutHeartbeatSeen = false;
    m_missingHeartbeatWarningLogged = false;
    m_readoutHeartbeatTimer.start();

    if (machineEventConnection || readoutConnection) {
        emit logMessage(QStringLiteral(
            "已启用反射球状态诊断：监视 Machine.ReadoutExt 实时读数心跳，"
            "并监听 ErrorMsg(ErrorType=2) 作为补充。"));
    } else {
        emit logMessage(QStringLiteral(
            "未能订阅 Machine.ReadoutExt/ErrorMsg，无法诊断“未找到反射球”状态。"));
    }

    m_consecutiveReadFailures = 0;
    m_alignmentRefreshCounter = 0;

    emit connectedChanged(true);
    emit logMessage(QStringLiteral("PC-DMIS Automation 接口连接成功。"));

    if (m_coordinateMode == 1) {
        refreshAlignmentMatrix(true);
    } else {
        // 仪器坐标系的原点就是激光跟踪仪位置。
        emit trackerOriginChanged(0.0, 0.0, 0.0, 0);
    }
}

void PcdmisWorker::disconnectFromPcdmis()
{
    const bool wasConnected = isConnected();
    releaseComObjects();
    emit connectedChanged(false);

    if (wasConnected) {
        emit logMessage(QStringLiteral("已断开 Qt 程序与 PC-DMIS Automation 接口的连接。"));
    }
}

void PcdmisWorker::setCoordinateMode(int modeIndex)
{
    const int normalizedMode = (modeIndex == 1) ? 1 : 0;
    if (m_coordinateMode == normalizedMode) {
        return;
    }

    m_coordinateMode = normalizedMode;
    m_consecutiveReadFailures = 0;

    if (m_coordinateMode == 0) {
        emit logMessage(QStringLiteral("坐标来源已切换为仪器坐标：Machine.ProbePosition。"));
        emit trackerOriginChanged(0.0, 0.0, 0.0, 0);
        if (isPolling()) {
            pollProbePosition();
        }
        return;
    }

    emit logMessage(QStringLiteral(
        "坐标来源已切换为当前 PC-DMIS 对齐坐标："
        "ProbePosition + MachineToPartMatrix。"));
    m_alignmentRefreshCounter = 0;
    if (isConnected()) {
        refreshAlignmentMatrix(true);
        if (isPolling()) {
            pollProbePosition();
        }
    }
}

void PcdmisWorker::setPollingEnabled(bool enabled)
{
    if (enabled) {
        if (!isConnected()) {
            emit errorOccurred(QStringLiteral("请先连接 PC-DMIS。"));
            emit pollingChanged(false);
            return;
        }

        if (m_pollTimer == nullptr) {
            emit errorOccurred(QStringLiteral("PC-DMIS 工作线程尚未初始化。"));
            emit pollingChanged(false);
            return;
        }

        if (!m_pollTimer->isActive()) {
            m_consecutiveReadFailures = 0;
            resetTrackingDetection();
            m_pollTimer->start();
            emit pollingChanged(true);
            emit logMessage(m_coordinateMode == 0
                                ? QStringLiteral("开始定时读取 ProbePosition。")
                                : QStringLiteral(
                                      "开始读取 ProbePosition 并转换到当前对齐坐标系。"));
            pollProbePosition();
        }
        return;
    }

    if (m_pollTimer != nullptr && m_pollTimer->isActive()) {
        m_pollTimer->stop();
        resetTrackingDetection();
        emit pollingChanged(false);
        emit logMessage(QStringLiteral("已停止定时读取。"));
    }
}

void PcdmisWorker::setPollingInterval(int milliseconds)
{
    m_pollingIntervalMs = qBound(20, milliseconds, 5000);
    if (m_pollTimer != nullptr) {
        m_pollTimer->setInterval(m_pollingIntervalMs);
    }
}

void PcdmisWorker::shutdown()
{
    // shutdown 由主线程在退出前以阻塞队列方式调用，因此 COM 对象仍在
    // 创建它们的工作线程中释放。
    releaseComObjects();
    if (m_comInitialized) {
        CoUninitialize();
        m_comInitialized = false;
    }
}

void PcdmisWorker::readOnce()
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    QString errorMessage;
    if (!readCurrentCoordinate(x, y, z, errorMessage)) {
        emit errorOccurred(errorMessage);
        return;
    }

    m_consecutiveReadFailures = 0;
    emit coordinateReceived(x, y, z, m_coordinateMode);
}

void PcdmisWorker::requestCoordinateSample(quint64 requestId)
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    QString errorMessage;
    const int sampleMode = m_coordinateMode;
    const bool success = readCurrentCoordinate(x, y, z, errorMessage);

    if (success) {
        m_consecutiveReadFailures = 0;
        // 同时更新主界面的实时坐标，再返回本次请求的专用结果。
        emit coordinateReceived(x, y, z, sampleMode);
    }
    emit coordinateSampleFinished(
        requestId, success, x, y, z, sampleMode, errorMessage);
}

bool PcdmisWorker::readCurrentCoordinate(double &x, double &y, double &z,
                                         QString &errorMessage,
                                         std::array<double, 3> *rawCoordinate)
{
    if (!isConnected()) {
        errorMessage = QStringLiteral("请先连接 PC-DMIS。");
        return false;
    }
    if (m_machine == nullptr || m_machine->isNull()) {
        errorMessage = QStringLiteral("Machine COM 对象已失效，请重新连接。");
        return false;
    }

    checkReadoutHeartbeat();

    QAxObject *point = m_machine->querySubObject("ProbePosition");
    if (point == nullptr || point->isNull()) {
        delete point;
        errorMessage = QStringLiteral(
            "读取 ProbePosition 失败。请确认跟踪仪在线、已回零并锁定反射球。");
        return false;
    }

    QVariant xValue = point->property("X");
    QVariant yValue = point->property("Y");
    QVariant zValue = point->property("Z");

    // 部分 PC-DMIS 类型库没有把 PointData 成员暴露成 Qt 属性，
    // 此时退回到动态 COM 调用。
    if (!xValue.isValid()) {
        xValue = point->dynamicCall("X");
    }
    if (!yValue.isValid()) {
        yValue = point->dynamicCall("Y");
    }
    if (!zValue.isValid()) {
        zValue = point->dynamicCall("Z");
    }
    delete point;

    bool xOk = false;
    bool yOk = false;
    bool zOk = false;
    x = xValue.toDouble(&xOk);
    y = yValue.toDouble(&yOk);
    z = zValue.toDouble(&zOk);

    if (!xOk || !yOk || !zOk) {
        emit logMessage(QStringLiteral(
            "PointData类型诊断：X=%1(%2)，Y=%3(%4)，Z=%5(%6)。")
                            .arg(QString::fromLatin1(
                                xValue.typeName() ? xValue.typeName() : "invalid"))
                            .arg(xValue.isValid()
                                     ? xValue.toString()
                                     : QStringLiteral("无效"))
                            .arg(QString::fromLatin1(
                                yValue.typeName() ? yValue.typeName() : "invalid"))
                            .arg(yValue.isValid()
                                     ? yValue.toString()
                                     : QStringLiteral("无效"))
                            .arg(QString::fromLatin1(
                                zValue.typeName() ? zValue.typeName() : "invalid"))
                            .arg(zValue.isValid()
                                     ? zValue.toString()
                                     : QStringLiteral("无效")));
        errorMessage = QStringLiteral(
            "ProbePosition 已返回，但 X/Y/Z 不是有效数值。请检查 PC-DMIS 的设备状态。");
        return false;
    }

    // 跟踪状态必须使用坐标转换前的仪器原始值，避免矩阵计算影响比较结果。
    if (rawCoordinate != nullptr) {
        *rawCoordinate = {x, y, z};
    }

    if (m_coordinateMode == 1) {
        ++m_alignmentRefreshCounter;
        const bool needsRefresh =
            !m_matrixValuesValid || m_alignmentRefreshCounter >= 10;
        if (needsRefresh) {
            m_alignmentRefreshCounter = 0;
            if (!refreshAlignmentMatrix(!m_matrixValuesValid)) {
                errorMessage = QStringLiteral(
                    "无法读取当前活动对齐的 MachineToPartMatrix 数值。"
                    "请确认测量程序中已经建立并激活坐标系。");
                return false;
            }
        }

        double partX = 0.0;
        double partY = 0.0;
        double partZ = 0.0;
        if (!transformPoint(x, y, z, partX, partY, partZ)) {
            errorMessage = QStringLiteral(
                "无法使用 MachineToPartMatrix 的 12 个数值转换 ProbePosition。"
                "请查看前面的矩阵诊断日志。");
            return false;
        }
        x = partX;
        y = partY;
        z = partZ;
    }

    errorMessage.clear();
    return true;
}

void PcdmisWorker::handleContinuousReadFailure(const QString &errorMessage)
{
    ++m_consecutiveReadFailures;
    if (m_consecutiveReadFailures != kFailureLimit) {
        return;
    }

    // 连续读取失败达到阈值时只切换跟踪状态，不能停止轮询。
    // 定时器继续读取 ProbePosition，读数恢复后才能检测到并发送 Tracking。
    setTrackingState(TrackingState::Lost, QStringLiteral("反射球丢失。"));
    if (!errorMessage.isEmpty()) {
        emit logMessage(QStringLiteral("坐标读取失败：%1").arg(errorMessage));
    }
}

void PcdmisWorker::pollProbePosition()
{
    checkReadoutHeartbeat();

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    std::array<double, 3> rawCoordinate{};
    QString errorMessage;
    if (!readCurrentCoordinate(x, y, z, errorMessage, &rawCoordinate)) {
        handleContinuousReadFailure(errorMessage);
        return;
    }

    m_consecutiveReadFailures = 0;
    updateTrackingState(rawCoordinate);
    // 跟踪状态只用于主界面提示和颜色显示，不改变原有坐标发布流程。
    emit coordinateReceived(x, y, z, m_coordinateMode);
}

void PcdmisWorker::updateTrackingState(
    const std::array<double, 3> &rawCoordinate)
{
    // 第一组坐标只作为比较基准，不立即判断跟踪状态。
    if (!m_lastRawCoordinateValid) {
        m_lastRawCoordinate = rawCoordinate;
        m_lastRawCoordinateValid = true;
        m_identicalCoordinateCount = 1;
        return;
    }

    const bool identical =
        rawCoordinate[0] == m_lastRawCoordinate[0] &&
        rawCoordinate[1] == m_lastRawCoordinate[1] &&
        rawCoordinate[2] == m_lastRawCoordinate[2];
    m_lastRawCoordinate = rawCoordinate;

    if (identical) {
        ++m_identicalCoordinateCount;
        if (m_identicalCoordinateCount >= kIdenticalCoordinateLimit) {
            setTrackingState(
                TrackingState::Lost,
                QStringLiteral("反射球丢失。"));
        }
        return;
    }

    // 当前坐标已经变化，它是新一轮连续相同判断的第一个样本。
    m_identicalCoordinateCount = 1;
    if (m_trackingState == TrackingState::Lost) {
        // 丢失状态下只要原始坐标重新变化，就说明 PC-DMIS 已恢复实时读数。
        setTrackingState(
            TrackingState::Tracking,
            QStringLiteral("反射球重新捕获，跟踪恢复。"));
        return;
    }

    setTrackingState(
        TrackingState::Tracking,
        QStringLiteral("反射球跟踪正常。"));
}

void PcdmisWorker::setTrackingState(TrackingState state,
                                    const QString &message)
{
    // 状态未变化时不重复发信号，避免主界面日志不断刷屏。
    if (m_trackingState == state) {
        return;
    }

    m_trackingState = state;
    emit trackingStateChanged(state, message);
}

void PcdmisWorker::resetTrackingDetection()
{
    // 新一轮读取必须重新积累样本，不能沿用上一次的重复计数。
    m_identicalCoordinateCount = 0;
    m_lastRawCoordinateValid = false;
    m_lastRawCoordinate.fill(0.0);
    setTrackingState(TrackingState::Unknown, QString());
}

void PcdmisWorker::onMachineError(const QString &message, int errorType)
{
    if (errorType != kReflectorNotFoundErrorType) {
        return;
    }

    setReflectorAvailability(
        false,
        message.trimmed().isEmpty()
            ? QStringLiteral(
                  "PC-DMIS 报告未找到反射球（ErrorType=2），当前坐标无效。")
            : QStringLiteral(
                  "PC-DMIS 报告未找到反射球（ErrorType=2）：%1")
                  .arg(message.trimmed()));
}

void PcdmisWorker::onMachineReadoutExt(double x, double y, double z)
{
    Q_UNUSED(x)
    Q_UNUSED(y)
    Q_UNUSED(z)
    noteReadoutHeartbeat();
}

void PcdmisWorker::onMachineEvent(const QString &name, int argumentCount,
                                  void *arguments)
{
    const qsizetype signatureStart = name.indexOf(QLatin1Char('('));
    const QString eventName =
        signatureStart >= 0 ? name.left(signatureStart) : name;
    if (eventName.compare(QStringLiteral("ReadoutExt"),
                          Qt::CaseInsensitive) == 0) {
        noteReadoutHeartbeat();
        return;
    }

    if (eventName.compare(QStringLiteral("ErrorMsg"),
                          Qt::CaseInsensitive) != 0) {
        return;
    }

    // COM 的 DISPPARAMS.rgvarg 参数顺序与事件声明相反：
    // ErrorMsg(Msg, ErrorType) 对应 [0]=ErrorType、[1]=Msg。
    if (argumentCount < 2 || arguments == nullptr) {
        emit logMessage(QStringLiteral(
            "诊断：收到 Machine.ErrorMsg，但事件参数不完整，无法读取错误类型。"));
        return;
    }

    const auto *eventArguments =
        static_cast<const VARIANTARG *>(arguments);
    int errorType = -1;
    if (!comVariantToInt(eventArguments[0], errorType)) {
        emit logMessage(QStringLiteral(
            "诊断：收到 Machine.ErrorMsg，但无法解析 ErrorType。"));
        return;
    }

    onMachineError(comVariantToString(eventArguments[1]), errorType);
}

void PcdmisWorker::noteReadoutHeartbeat()
{
    const bool firstHeartbeat = !m_readoutHeartbeatSeen;
    m_readoutHeartbeatSeen = true;
    m_readoutHeartbeatTimer.restart();

    if (firstHeartbeat) {
        emit logMessage(QStringLiteral(
            "反射球诊断已确认：开始收到 Machine.ReadoutExt 实时读数心跳。"));
    }

    setReflectorAvailability(
        true,
        m_reflectorState == ReflectorState::Unavailable
            ? QStringLiteral("反射球已重新锁定，Machine.ReadoutExt 实时读数已经恢复。")
            : QString());
}

void PcdmisWorker::checkReadoutHeartbeat()
{
    if (!isConnected() || !m_readoutHeartbeatTimer.isValid()) {
        return;
    }

    if (!m_readoutHeartbeatSeen) {
        if (!m_missingHeartbeatWarningLogged &&
            m_readoutHeartbeatTimer.elapsed() >= kReadoutStartupWarningMs) {
            m_missingHeartbeatWarningLogged = true;
            emit logMessage(QStringLiteral(
                "诊断：连续读取 3 秒仍未收到 Machine.ReadoutExt。"
                "当前 PC-DMIS/控制器没有向 Automation 客户端提供实时读数心跳，"
                "因此不能用此接口判断界面红色状态。"));
        }
        return;
    }

    if (m_readoutHeartbeatTimer.elapsed() >= kReadoutLossTimeoutMs) {
        setReflectorAvailability(
            false,
            QStringLiteral(
                "未找到反射球：Machine.ReadoutExt 实时读数已中断超过 1 秒，"
                "当前坐标无效。"));
    }
}

void PcdmisWorker::setReflectorAvailability(bool available,
                                             const QString &reason)
{
    const ReflectorState newState =
        available ? ReflectorState::Available : ReflectorState::Unavailable;
    if (m_reflectorState == newState) {
        return;
    }

    const ReflectorState previousState = m_reflectorState;
    m_reflectorState = newState;
    emit measurementValidityChanged(available, reason);

    if (!available) {
        emit logMessage(QStringLiteral("诊断：%1").arg(reason));
    } else if (previousState == ReflectorState::Unavailable &&
               !reason.isEmpty()) {
        emit logMessage(QStringLiteral("诊断：%1").arg(reason));
    }
}

bool PcdmisWorker::refreshAlignmentMatrix(bool logSuccess)
{
    releaseAlignmentObjects();

    if (m_activePartProgram == nullptr || m_activePartProgram->isNull()) {
        if (logSuccess) {
            emit logMessage(QStringLiteral(
                "没有取得 ActivePartProgram，无法读取当前活动对齐矩阵。"));
        }
        return false;
    }

    m_commands = m_activePartProgram->querySubObject("Commands");
    if (m_commands == nullptr || m_commands->isNull()) {
        releaseAlignmentObjects();
        if (logSuccess) {
            emit logMessage(QStringLiteral(
                "没有取得 ActivePartProgram.Commands 集合。"));
        }
        return false;
    }

    m_currentAlignmentCommand =
        m_commands->querySubObject("CurrentAlignment");
    if (m_currentAlignmentCommand == nullptr ||
        m_currentAlignmentCommand->isNull()) {
        releaseAlignmentObjects();
        if (logSuccess) {
            emit logMessage(QStringLiteral(
                "Commands.CurrentAlignment 为空。请先在 PC-DMIS 中建立并激活对齐。"));
        }
        return false;
    }

    QString alignmentId = m_currentAlignmentCommand->property("ID").toString();
    if (alignmentId.isEmpty()) {
        alignmentId =
            m_currentAlignmentCommand->dynamicCall("ID").toString();
    }
    QString alignmentType =
        m_currentAlignmentCommand->property("TypeDescription").toString();
    if (alignmentType.isEmpty()) {
        alignmentType =
            m_currentAlignmentCommand->dynamicCall("TypeDescription").toString();
    }

    m_alignmentCommand =
        m_currentAlignmentCommand->querySubObject("AlignmentCommand");
    if (m_alignmentCommand == nullptr || m_alignmentCommand->isNull()) {
        releaseAlignmentObjects();
        if (logSuccess) {
            emit logMessage(QStringLiteral(
                "CurrentAlignment 不能转换为 AlignmentCommand。"));
        }
        return false;
    }

    m_machineToPartMatrix =
        m_alignmentCommand->querySubObject("MachineToPartMatrix");
    if (m_machineToPartMatrix == nullptr ||
        m_machineToPartMatrix->isNull()) {
        releaseAlignmentObjects();
        if (logSuccess) {
            emit logMessage(QStringLiteral(
                "当前 AlignmentCommand 没有返回 MachineToPartMatrix。"));
        }
        return false;
    }

    connect(m_machineToPartMatrix, &QAxObject::exception,
            this, &PcdmisWorker::onComException);

    QVariant identityValue =
        m_machineToPartMatrix->property("IsIdentity");
    if (!identityValue.isValid()) {
        identityValue = m_machineToPartMatrix->dynamicCall("IsIdentity");
    }
    m_matrixIdentityKnown = identityValue.isValid();
    m_matrixIsIdentity =
        m_matrixIdentityKnown && identityValue.toBool();

    m_matrixValuesValid = true;
    for (int index = 0; index < static_cast<int>(m_matrixValues.size()); ++index) {
        bool valueOk = false;
        const QVariant value = m_machineToPartMatrix->dynamicCall(
            "Item(int)", index + 1);
        m_matrixValues[static_cast<std::size_t>(index)] =
            value.toDouble(&valueOk);
        if (!valueOk) {
            m_matrixValuesValid = false;
            break;
        }
    }
    if (!m_matrixValuesValid) {
        if (logSuccess) {
            emit logMessage(QStringLiteral(
                "MachineToPartMatrix 已取得，但无法读取 Item(1)..Item(12)。"));
        }
        return false;
    }

    const QString description =
        QStringLiteral("%1 / %2")
            .arg(alignmentId.isEmpty() ? QStringLiteral("<无 ID>") : alignmentId,
                 alignmentType.isEmpty() ? QStringLiteral("<未知类型>") : alignmentType);
    const bool alignmentChanged = description != m_lastAlignmentDescription;
    m_lastAlignmentDescription = description;

    if (logSuccess || alignmentChanged) {
        emit logMessage(QStringLiteral(
            "已取得当前活动对齐：%1；MachineToPartMatrix：%2。")
                            .arg(description,
                                 m_matrixIdentityKnown && m_matrixIsIdentity
                                     ? QStringLiteral("单位矩阵")
                                     : QStringLiteral("有效转换矩阵")));
        emit logMessage(QStringLiteral(
            "矩阵明细：Offset=(%1,%2,%3)，X轴=(%4,%5,%6)，"
            "Y轴=(%7,%8,%9)，Z轴=(%10,%11,%12)。")
                            .arg(m_matrixValues[0], 0, 'f', 9)
                            .arg(m_matrixValues[1], 0, 'f', 9)
                            .arg(m_matrixValues[2], 0, 'f', 9)
                            .arg(m_matrixValues[3], 0, 'f', 9)
                            .arg(m_matrixValues[4], 0, 'f', 9)
                            .arg(m_matrixValues[5], 0, 'f', 9)
                            .arg(m_matrixValues[6], 0, 'f', 9)
                            .arg(m_matrixValues[7], 0, 'f', 9)
                            .arg(m_matrixValues[8], 0, 'f', 9)
                            .arg(m_matrixValues[9], 0, 'f', 9)
                            .arg(m_matrixValues[10], 0, 'f', 9)
                            .arg(m_matrixValues[11], 0, 'f', 9));
    }

    // 将仪器原点转换到当前对齐坐标系，供圆拟合时判断法向正反。
    const double deltaX = -m_matrixValues[0];
    const double deltaY = -m_matrixValues[1];
    const double deltaZ = -m_matrixValues[2];
    const double trackerX = deltaX * m_matrixValues[3] +
                            deltaY * m_matrixValues[4] +
                            deltaZ * m_matrixValues[5];
    const double trackerY = deltaX * m_matrixValues[6] +
                            deltaY * m_matrixValues[7] +
                            deltaZ * m_matrixValues[8];
    const double trackerZ = deltaX * m_matrixValues[9] +
                            deltaY * m_matrixValues[10] +
                            deltaZ * m_matrixValues[11];
    m_alignedTrackerOrigin = {trackerX, trackerY, trackerZ};
    m_alignedTrackerOriginValid = true;
    // 这里得到的始终是“对齐坐标”中的原点。附带模式值可以防止
    // TestPoints 单独刷新矩阵时污染主界面的仪器坐标状态。
    emit trackerOriginChanged(trackerX, trackerY, trackerZ, 1);

    return true;
}

bool PcdmisWorker::transformPoint(double machineX, double machineY,
                                  double machineZ, double &partX,
                                  double &partY, double &partZ)
{
    if (!m_matrixValuesValid) {
        return false;
    }

    // For MachineToPartMatrix, Offset is the part-coordinate origin expressed
    // in machine coordinates. First translate the machine point to that origin,
    // then project it onto the X/Y/Z alignment axes.
    const double deltaX = machineX - m_matrixValues[0];
    const double deltaY = machineY - m_matrixValues[1];
    const double deltaZ = machineZ - m_matrixValues[2];
    partX = deltaX * m_matrixValues[3] +
            deltaY * m_matrixValues[4] +
            deltaZ * m_matrixValues[5];
    partY = deltaX * m_matrixValues[6] +
            deltaY * m_matrixValues[7] +
            deltaZ * m_matrixValues[8];
    partZ = deltaX * m_matrixValues[9] +
            deltaY * m_matrixValues[10] +
            deltaZ * m_matrixValues[11];

    const bool unchanged =
        qAbs(partX - machineX) <= 1.0e-12 &&
        qAbs(partY - machineY) <= 1.0e-12 &&
        qAbs(partZ - machineZ) <= 1.0e-12;
    if (m_matrixIdentityKnown && !m_matrixIsIdentity && unchanged) {
        emit logMessage(QStringLiteral(
            "手动矩阵乘法完成，但非单位矩阵没有改变坐标；请检查矩阵明细。"));
        return false;
    }

    if (!m_loggedTransformSuccess) {
        m_loggedTransformSuccess = true;
        emit logMessage(QStringLiteral(
            "矩阵转换已生效：仪器坐标 (%1, %2, %3) → 对齐坐标 (%4, %5, %6)。")
                            .arg(machineX, 0, 'f', 6)
                            .arg(machineY, 0, 'f', 6)
                            .arg(machineZ, 0, 'f', 6)
                            .arg(partX, 0, 'f', 6)
                            .arg(partY, 0, 'f', 6)
                            .arg(partZ, 0, 'f', 6));
    }

    return true;
}

void PcdmisWorker::onComException(int code, const QString &source,
                                  const QString &description,
                                  const QString &help)
{
    QString message = QStringLiteral(
        "PC-DMIS COM 异常：代码 %1，来源 %2，说明 %3。")
                          .arg(code)
                          .arg(source.isEmpty() ? QStringLiteral("<未知>") : source)
                          .arg(description.isEmpty() ? QStringLiteral("<无>") : description);
    if (!help.isEmpty()) {
        message += QStringLiteral(" 帮助：%1").arg(help);
    }
    emit logMessage(message);
}

void PcdmisWorker::releaseAlignmentObjects()
{
    m_matrixValuesValid = false;
    m_matrixIdentityKnown = false;
    m_matrixIsIdentity = false;
    m_alignedTrackerOriginValid = false;
    delete m_machineToPartMatrix;
    m_machineToPartMatrix = nullptr;
    delete m_alignmentCommand;
    m_alignmentCommand = nullptr;
    delete m_currentAlignmentCommand;
    m_currentAlignmentCommand = nullptr;
    delete m_commands;
    m_commands = nullptr;
}

QAxObject *PcdmisWorker::selectMachine(QAxObject *machines)
{
    if (machines == nullptr) {
        return nullptr;
    }

    // A Machine is bound to a PartProgram. Prefer the machine associated with
    // the active online measurement routine, avoiding an OFFLINE collection item.
    m_activePartProgram = m_application->querySubObject("ActivePartProgram");
    if (m_activePartProgram != nullptr && !m_activePartProgram->isNull()) {
        QAxObject *activeMachine =
            m_activePartProgram->querySubObject("ActiveMachine");
        if (activeMachine != nullptr && !activeMachine->isNull()) {
            const QString name = activeMachine->property("Name").toString();
            emit logMessage(QStringLiteral("已选择当前测量程序的 ActiveMachine：%1。")
                                .arg(name.isEmpty() ? QStringLiteral("<未命名>") : name));
            return activeMachine;
        }
        delete activeMachine;
        delete m_activePartProgram;
        m_activePartProgram = nullptr;
    } else {
        delete m_activePartProgram;
        m_activePartProgram = nullptr;
    }

    bool countOk = false;
    const int count = machines->property("Count").toInt(&countOk);
    emit logMessage(QStringLiteral("Machines.Count = %1。")
                        .arg(countOk ? count : -1));

    QAxObject *fallback = nullptr;

    // The documentation does not state whether a particular PC-DMIS version
    // uses a zero-based or one-based collection, so test both ranges.
    for (int index = 0; index <= qMax(count, 1); ++index) {
        QAxObject *candidate = machineAt(machines, index);
        if (candidate == nullptr || candidate->isNull()) {
            delete candidate;
            continue;
        }

        const QString name = candidate->property("Name").toString();
        emit logMessage(QStringLiteral("发现 Machine[%1]：%2。")
                            .arg(index)
                            .arg(name.isEmpty() ? QStringLiteral("<未命名>") : name));

        if (fallback == nullptr) {
            fallback = candidate;
        } else {
            delete candidate;
        }
    }

    return fallback;
}

QAxObject *PcdmisWorker::machineAt(QAxObject *machines, int index) const
{
    if (machines == nullptr) {
        return nullptr;
    }

    QAxObject *machine = machines->querySubObject(
        "Item(QVariant)", QVariant(index));

    if (machine == nullptr || machine->isNull()) {
        delete machine;
        machine = machines->querySubObject("Item(int)", index);
    }

    if (machine == nullptr || machine->isNull()) {
        delete machine;
        machine = machines->querySubObject(
            "_Item(QVariant)", QVariant(index));
    }

    return machine;
}

void PcdmisWorker::releaseComObjects()
{
    if (m_pollTimer != nullptr && m_pollTimer->isActive()) {
        m_pollTimer->stop();
        emit pollingChanged(false);
    }

    releaseAlignmentObjects();
    delete m_machine;
    m_machine = nullptr;
    delete m_activePartProgram;
    m_activePartProgram = nullptr;
    delete m_machines;
    m_machines = nullptr;
    delete m_application;
    m_application = nullptr;
    m_consecutiveReadFailures = 0;
    m_alignmentRefreshCounter = 0;
    m_matrixIdentityKnown = false;
    m_matrixIsIdentity = false;
    m_matrixValuesValid = false;
    m_loggedTransformSuccess = false;
    resetTrackingDetection();
    m_reflectorState = ReflectorState::Unknown;
    m_readoutHeartbeatSeen = false;
    m_missingHeartbeatWarningLogged = false;
    m_readoutHeartbeatTimer.invalidate();
    m_alignedTrackerOrigin.fill(0.0);
    m_alignedTrackerOriginValid = false;
    m_matrixValues.fill(0.0);
    m_lastAlignmentDescription.clear();
}
