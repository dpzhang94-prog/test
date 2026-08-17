#include "mainwindow.h"
#include "features/testpoints/testpoints.h"
#include "pcdmisclient.h"
#include "tcpserverworker.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QColor>
#include <QDir>
#include <QFileDialog>
#include <QHeaderView>
#include <QMetaObject>
#include <QMessageBox>
#include <QRegularExpression>
#include <QSaveFile>
#include <QStatusBar>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QThread>

#include <array>
#include <cmath>
#include <set>

namespace {
constexpr double kTcpCenterWarningDistanceMm = 10.0;

QTableWidgetItem *numberItem(double value, int precision = 6)
{
    auto *item = new QTableWidgetItem(
        QString::number(value, 'f', precision));
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_client(new PcdmisClient(this))
{
    ui->setupUi(this);

    connect(ui->connectButton, &QPushButton::clicked,
            this, &MainWindow::connectPcdmis);
    connect(ui->disconnectButton, &QPushButton::clicked,
            this, &MainWindow::disconnectPcdmis);
    connect(ui->startButton, &QPushButton::clicked,
            this, &MainWindow::startPolling);
    connect(ui->stopButton, &QPushButton::clicked,
            this, &MainWindow::stopPolling);
    connect(ui->readOnceButton, &QPushButton::clicked,
            m_client, &PcdmisClient::readOnce);
    connect(ui->clearLogButton, &QPushButton::clicked,
            ui->logEdit, &QPlainTextEdit::clear);
    connect(ui->testPointsButton, &QPushButton::clicked,
            this, &MainWindow::openTestPointsDialog);
    connect(ui->startTcpServerButton, &QPushButton::clicked,
            this, &MainWindow::startTcpServer);
    connect(ui->stopTcpServerButton, &QPushButton::clicked,
            this, &MainWindow::stopTcpServer);
    connect(ui->captureCirclePointButton, &QPushButton::clicked,
            this, &MainWindow::captureCirclePoint);
    connect(ui->deleteCirclePointButton, &QPushButton::clicked,
            this, &MainWindow::deleteSelectedCirclePoints);
    connect(ui->clearCirclePointsButton, &QPushButton::clicked,
            this, &MainWindow::clearCirclePoints);
    connect(ui->calculateCircleButton, &QPushButton::clicked,
            this, &MainWindow::calculateCircle);
    connect(ui->exportCircleResultsButton, &QPushButton::clicked,
            this, &MainWindow::exportCircleResults);

    connect(ui->intervalSpinBox, &QSpinBox::valueChanged,
            m_client, &PcdmisClient::setPollingInterval);
    connect(ui->coordinateModeComboBox, &QComboBox::currentIndexChanged,
            this, [this](int index) {
                m_hasTrackerOrigin = (index == 0);
                if (index == 0) {
                    m_trackerOrigin = {};
                }
                m_client->setCoordinateMode(index);
                if (index == 0) {
                    ui->coordinateSystemLabel->setText(QStringLiteral(
                        "当前数据源：Machine.ProbePosition（仪器坐标系；单位由 PC-DMIS 当前设置决定）"));
                } else {
                    ui->coordinateSystemLabel->setText(QStringLiteral(
                        "当前数据源：ProbePosition + MachineToPartMatrix"
                        "（当前 PC-DMIS 活动对齐坐标）"));
                }
                ui->xValueLabel->setText(QStringLiteral("--"));
                ui->yValueLabel->setText(QStringLiteral("--"));
                ui->zValueLabel->setText(QStringLiteral("--"));
                ui->sampleTimeLabel->setText(QStringLiteral("--"));
            });
    connect(m_client, &PcdmisClient::connectedChanged,
            this, &MainWindow::showConnectedState);
    connect(m_client, &PcdmisClient::pollingChanged,
            this, &MainWindow::showPollingState);
    connect(m_client, &PcdmisClient::coordinateReceived,
            this, &MainWindow::showCoordinate);
    connect(m_client, &PcdmisClient::coordinateSampleFinished,
            this, &MainWindow::finishCirclePointCapture);
    connect(m_client, &PcdmisClient::trackerOriginChanged,
            this, &MainWindow::setTrackerOrigin);
    connect(m_client, &PcdmisClient::trackingStateChanged,
            this, &MainWindow::showTrackingState);
    connect(m_client, &PcdmisClient::logMessage,
            this, &MainWindow::appendLog);
    connect(m_client, &PcdmisClient::errorOccurred,
            this, &MainWindow::showError);

    // TCP服务器使用独立线程，避免界面操作影响机器人心跳和收包。
    m_tcpThread = new QThread(this);
    m_tcpWorker = new TcpServerWorker;
    m_tcpWorker->moveToThread(m_tcpThread);
    connect(m_tcpThread, &QThread::finished,
            m_tcpWorker, &QObject::deleteLater);
    connect(this, &MainWindow::startTcpServerRequested,
            m_tcpWorker, &TcpServerWorker::startServer,
            Qt::QueuedConnection);
    connect(this, &MainWindow::stopTcpServerRequested,
            m_tcpWorker, &TcpServerWorker::stopServer,
            Qt::QueuedConnection);
    connect(this, &MainWindow::completeTcpBusinessRequestRequested,
            m_tcpWorker, &TcpServerWorker::completeBusinessRequest,
            Qt::QueuedConnection);
    connect(this, &MainWindow::discardTcpBusinessRequestRequested,
            m_tcpWorker, &TcpServerWorker::discardBusinessRequest,
            Qt::QueuedConnection);
    connect(m_tcpWorker, &TcpServerWorker::serverStateChanged,
            this, &MainWindow::showTcpServerState,
            Qt::QueuedConnection);
    connect(m_tcpWorker, &TcpServerWorker::businessRequestReceived,
            this, &MainWindow::handleRobotBusinessRequest,
            Qt::QueuedConnection);
    connect(m_tcpWorker, &TcpServerWorker::logMessage,
            this, &MainWindow::appendLog,
            Qt::QueuedConnection);
    m_tcpThread->start();

    m_client->setPollingInterval(ui->intervalSpinBox->value());
    ui->circlePointsTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Fixed);
    ui->circlePointsTable->setColumnWidth(0, 55);
    ui->circlePointsTable->setColumnWidth(1, 100);
    ui->circlePointsTable->setColumnWidth(2, 100);
    ui->circlePointsTable->setColumnWidth(3, 100);
    ui->circlePointsTable->setSelectionBehavior(
        QAbstractItemView::SelectRows);
    ui->circlePointsTable->setSelectionMode(
        QAbstractItemView::ExtendedSelection);
    // 空表格的位姿列平均分配，质量指标列按完整表头宽度展开。
    ui->circleResultTable->horizontalHeader()->setStretchLastSection(false);
    ui->circleResultTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    for (int column = 6;
         column < ui->circleResultTable->columnCount(); ++column) {
        ui->circleResultTable->horizontalHeader()->setSectionResizeMode(
            column, QHeaderView::ResizeToContents);
    }
    refreshCirclePointTable();
    showConnectedState(false);
    showPollingState(false);
    showTcpServerState(false, QString());
    statusBar()->showMessage(QStringLiteral("请先启动并配置 PC-DMIS，然后点击“连接 PC-DMIS”"));
    appendLog(QStringLiteral("程序已启动。当前读取的是 ProbePosition（仪器坐标系）。"));
}

MainWindow::~MainWindow()
{
    // 先在TCP对象所属线程关闭服务器，再结束线程。
    if (m_tcpThread != nullptr && m_tcpThread->isRunning() &&
        m_tcpWorker != nullptr) {
        QMetaObject::invokeMethod(
            m_tcpWorker, "stopServer", Qt::BlockingQueuedConnection);
        m_tcpThread->quit();
        m_tcpThread->wait();
    }
    m_tcpWorker = nullptr;

    // 先停止工作线程并在其所属线程内释放 COM，再销毁界面。
    delete m_client;
    m_client = nullptr;
    delete ui;
}

void MainWindow::connectPcdmis()
{
    m_client->connectToPcdmis(ui->visibleCheckBox->isChecked());
}

void MainWindow::disconnectPcdmis()
{
    m_client->disconnectFromPcdmis();
}

void MainWindow::startPolling()
{
    m_client->setPollingInterval(ui->intervalSpinBox->value());
    m_client->setPollingEnabled(true);
}

void MainWindow::stopPolling()
{
    m_client->setPollingEnabled(false);
}

void MainWindow::startTcpServer()
{
    ui->startTcpServerButton->setEnabled(false);
    emit startTcpServerRequested();
}

void MainWindow::stopTcpServer()
{
    ui->stopTcpServerButton->setEnabled(false);
    emit stopTcpServerRequested();
}

void MainWindow::showTcpServerState(
    bool running, const QString &listenAddress)
{
    ui->startTcpServerButton->setEnabled(!running);
    ui->stopTcpServerButton->setEnabled(running);
    ui->tcpServerStatusLabel->setText(
        running
            ? QStringLiteral("正在监听 %1:7788").arg(listenAddress)
            : QStringLiteral("服务器未启动"));
    ui->tcpServerStatusLabel->setStyleSheet(
        running
            ? QStringLiteral("color: #16803a; font-weight: bold;")
            : QStringLiteral("color: #777777;"));
}

void MainWindow::openTestPointsDialog()
{
    TestPoints dialog(m_client, this);
    connect(&dialog, &TestPoints::signal_path,
            this, [this](const QString &path) {
                appendLog(QStringLiteral("测试点文件已生成：%1").arg(path));
                statusBar()->showMessage(
                    QStringLiteral("测试点文件已生成：%1").arg(path), 10000);
            });
    dialog.exec();
}

void MainWindow::captureCirclePoint()
{
    if (isRobotMeasurementActive()) {
        return;
    }

    if (!m_client->isConnected()) {
        QMessageBox::information(
            this, QStringLiteral("无法采集"),
            QStringLiteral("请先连接 PC-DMIS。"));
        return;
    }

    if (m_circleCapturePending) {
        return;
    }

    const int currentMode = ui->coordinateModeComboBox->currentIndex();
    if (!m_circlePoints.empty() &&
        currentMode != m_circlePointCoordinateMode) {
        QMessageBox::information(
            this, QStringLiteral("坐标系不一致"),
            QStringLiteral(
                "已有采集点来自另一个坐标系。请先清空采集点，"
                "再使用当前坐标系重新采集。"));
        return;
    }

    // PC-DMIS 读取现在位于工作线程，按钮请求必须等待专用完成信号，
    // 不能再在 readOnce() 后立即检查主线程中的旧坐标。
    m_circleCapturePending = true;
    m_circleCaptureSource = CircleCaptureSource::Manual;
    m_pendingCircleCaptureId = m_nextCoordinateRequestId++;
    ui->captureCirclePointButton->setEnabled(false);
    statusBar()->showMessage(QStringLiteral("正在读取本次圆周采集点..."));
    m_client->requestCoordinateSample(m_pendingCircleCaptureId);
}

void MainWindow::finishCirclePointCapture(
    quint64 requestId, bool success,
    double x, double y, double z,
    int coordinateMode, const QString &errorMessage)
{
    if (!m_circleCapturePending ||
        requestId != m_pendingCircleCaptureId) {
        return;
    }

    const CircleCaptureSource captureSource = m_circleCaptureSource;
    const quint64 robotRequestToken = m_pendingRobotRequestToken;
    const QString robotPayload = m_pendingRobotPayload;
    m_circleCapturePending = false;
    m_circleCaptureSource = CircleCaptureSource::None;
    m_pendingCircleCaptureId = 0;
    refreshCirclePointTable();

    const auto rejectRobotCapture =
        [this, robotRequestToken, robotPayload](const QString &reason) {
            m_robotMeasurementState = RobotMeasurementState::Error;
            m_pendingRobotRequestToken = 0;
            m_pendingRobotPayload.clear();
            refreshCirclePointTable();
            rejectRobotRequest(robotRequestToken, robotPayload, reason);
        };

    if (!success) {
        if (captureSource == CircleCaptureSource::Robot) {
            rejectRobotCapture(
                errorMessage.isEmpty()
                    ? QStringLiteral("没有取得有效坐标，请确认靶球已经锁定")
                    : errorMessage);
            return;
        }

        refreshCirclePointTable();
        statusBar()->showMessage(QStringLiteral("本次圆周点读取失败"), 5000);
        QMessageBox::information(
            this, QStringLiteral("无法采集"),
            errorMessage.isEmpty()
                ? QStringLiteral("本次没有取得有效坐标，请确认靶球已经锁定。")
                : errorMessage);
        return;
    }

    const int currentMode = ui->coordinateModeComboBox->currentIndex();
    if (coordinateMode != currentMode) {
        if (captureSource == CircleCaptureSource::Robot) {
            rejectRobotCapture(QStringLiteral("读取期间坐标系发生变化"));
            return;
        }
        QMessageBox::information(
            this, QStringLiteral("坐标系已切换"),
            QStringLiteral("读取期间坐标系发生变化，本次结果未采集，请重新操作。"));
        return;
    }
    if (!m_circlePoints.empty() &&
        currentMode != m_circlePointCoordinateMode) {
        if (captureSource == CircleCaptureSource::Robot) {
            rejectRobotCapture(QStringLiteral("当前点位的采样坐标系不一致"));
            return;
        }
        QMessageBox::information(
            this, QStringLiteral("坐标系不一致"),
            QStringLiteral(
                "已有采集点来自另一个坐标系。请先清空采集点，"
                "再使用当前坐标系重新采集。"));
        return;
    }
    if (!m_hasTrackerOrigin) {
        if (captureSource == CircleCaptureSource::Robot) {
            rejectRobotCapture(QStringLiteral(
                "尚未取得激光跟踪仪在当前坐标系中的位置"));
            return;
        }
        QMessageBox::information(
            this, QStringLiteral("无法确定法向"),
            QStringLiteral(
                "尚未取得激光跟踪仪在当前坐标系中的位置，"
                "请确认当前 PC-DMIS 对齐矩阵有效。"));
        return;
    }

    if (m_circlePoints.empty()) {
        m_circlePointCoordinateMode = currentMode;
    }
    const GeometryPoint capturedPoint{x, y, z};
    m_circlePoints.push_back(capturedPoint);

    if (captureSource == CircleCaptureSource::Robot) {
        m_robotMeasurementState = RobotMeasurementState::ReadyForCommand;
        m_pendingRobotRequestToken = 0;
        m_pendingRobotPayload.clear();
        refreshCirclePointTable();
        appendLog(QStringLiteral(
                      "机器人点位 P%1/%2 已采集第 %3 个圆周点：(%4, %5, %6)。")
                      .arg(m_robotCurrentPoint)
                      .arg(m_robotTotalPoints)
                      .arg(m_circlePoints.size())
                      .arg(capturedPoint.x, 0, 'f', 6)
                      .arg(capturedPoint.y, 0, 'f', 6)
                      .arg(capturedPoint.z, 0, 'f', 6));
        statusBar()->showMessage(QStringLiteral("机器人圆周点采集完成"), 3000);
        completeRobotRequest(robotRequestToken);
        return;
    }

    refreshCirclePointTable();
    appendLog(QStringLiteral("已采集圆周点 #%1：(%2, %3, %4)。")
                  .arg(m_circlePoints.size())
                  .arg(capturedPoint.x, 0, 'f', 6)
                  .arg(capturedPoint.y, 0, 'f', 6)
                  .arg(capturedPoint.z, 0, 'f', 6));
    statusBar()->showMessage(QStringLiteral("圆周点采集完成"), 3000);
}

void MainWindow::deleteSelectedCirclePoints()
{
    if (isRobotMeasurementActive()) {
        return;
    }

    std::set<int, std::greater<int>> rows;
    for (const QModelIndex &index :
         ui->circlePointsTable->selectionModel()->selectedRows()) {
        rows.insert(index.row());
    }
    for (const int row : rows) {
        if (row >= 0 &&
            row < static_cast<int>(m_circlePoints.size())) {
            m_circlePoints.erase(m_circlePoints.begin() + row);
        }
    }
    if (m_circlePoints.empty()) {
        m_circlePointCoordinateMode = -1;
    }
    refreshCirclePointTable();
}

void MainWindow::clearCirclePoints()
{
    if (isRobotMeasurementActive()) {
        return;
    }

    m_circlePoints.clear();
    m_measurementResults.clear();
    m_circlePointCoordinateMode = -1;
    m_robotMeasurementState = RobotMeasurementState::Idle;
    m_robotCurrentPoint = 0;
    m_robotTotalPoints = 0;
    m_lastCompletedRobotPoint = 0;
    ui->circleResultTable->setRowCount(0);
    ui->circleResultTable->horizontalHeader()->setStretchLastSection(false);
    ui->circleResultTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    for (int column = 6;
         column < ui->circleResultTable->columnCount(); ++column) {
        ui->circleResultTable->horizontalHeader()->setSectionResizeMode(
            column, QHeaderView::ResizeToContents);
    }
    refreshCirclePointTable();
    appendLog(QStringLiteral("已清空圆周采集点和计算结果。"));
}

void MainWindow::calculateCircle()
{
    if (isRobotMeasurementActive()) {
        return;
    }

    if (!m_hasTrackerOrigin) {
        QMessageBox::information(
            this, QStringLiteral("无法计算"),
            QStringLiteral("尚未取得激光跟踪仪在当前坐标系中的位置。"));
        return;
    }

    CircleFitResult result =
        GeometryCalculator::fitCircle(m_circlePoints, m_trackerOrigin);
    if (!result.success) {
        QMessageBox::information(
            this, QStringLiteral("计算失败"), result.errorMessage);
        return;
    }

    applyTcpZOffset(result);

    showCircleResult(result);
    appendLog(QStringLiteral(
                  "圆拟合完成：圆心=(%1, %2, %3)，"
                  "A=%4°，B=%5°，C=0°，半径=%6。")
                  .arg(result.center.x, 0, 'f', 6)
                  .arg(result.center.y, 0, 'f', 6)
                  .arg(result.center.z, 0, 'f', 6)
                  .arg(result.angleA, 0, 'f', 6)
                  .arg(result.angleB, 0, 'f', 6)
                  .arg(result.radius, 0, 'f', 6));
}

void MainWindow::exportCircleResults()
{
    if (m_measurementResults.empty() || isRobotMeasurementActive()) {
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
        this, QStringLiteral("导出圆心与姿态结果"),
        QDir::homePath() + QStringLiteral("/圆心与姿态结果.csv"),
        QStringLiteral("CSV 表格 (*.csv)"));
    if (filePath.isEmpty()) {
        return;
    }
    if (!filePath.endsWith(QStringLiteral(".csv"),
                           Qt::CaseInsensitive)) {
        filePath += QStringLiteral(".csv");
    }

    QSaveFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(
            this, QStringLiteral("导出失败"),
            QStringLiteral("无法创建CSV文件：%1")
                .arg(file.errorString()));
        return;
    }

    // 写入UTF-8 BOM，保证常用表格软件能正确识别中文列标题。
    file.write("\xEF\xBB\xBF", 3);
    QTextStream stream(&file);
    stream << QStringLiteral("点名,J1,J2,J3,J4,J5,J6, ,X,Y,Z,I,J,K\n");

    for (const MeasurementResultRecord &record : m_measurementResults) {
        QStringList fields;
        fields.reserve(14);
        fields.append(QStringLiteral("P%1").arg(record.pointIndex));
        for (double joint : record.joints) {
            fields.append(formatCsvNumber(joint));
        }
        fields.append(QStringLiteral("0"));
        fields.append(QString());
        fields.append(formatCsvNumber(record.circle.center.x));
        fields.append(formatCsvNumber(record.circle.center.y));
        fields.append(formatCsvNumber(record.circle.center.z));
        fields.append(formatCsvNumber(record.circle.angleA));
        fields.append(formatCsvNumber(record.circle.angleB));
        fields.append(formatCsvNumber(record.circle.angleC));
        stream << fields.join(QChar(',')) << QChar('\n');
    }

    stream.flush();
    if (stream.status() != QTextStream::Ok || !file.commit()) {
        QMessageBox::warning(
            this, QStringLiteral("导出失败"),
            QStringLiteral("CSV文件写入失败：%1")
                .arg(file.errorString()));
        return;
    }

    appendLog(QStringLiteral("已导出 %1 条圆心与姿态结果：%2")
                  .arg(m_measurementResults.size())
                  .arg(filePath));
    statusBar()->showMessage(
        QStringLiteral("结果已导出：%1").arg(filePath), 10000);
}

void MainWindow::showCoordinate(double x, double y, double z)
{
    constexpr char format = 'f';
    constexpr int precision = 6;
    ui->xValueLabel->setText(QString::number(x, format, precision));
    ui->yValueLabel->setText(QString::number(y, format, precision));
    ui->zValueLabel->setText(QString::number(z, format, precision));
    ui->sampleTimeLabel->setText(
        QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss.zzz")));
}

void MainWindow::setTrackerOrigin(double x, double y, double z)
{
    m_trackerOrigin = {x, y, z};
    m_hasTrackerOrigin = true;
}

void MainWindow::showTrackingState(TrackingState state,
                                   const QString &message)
{
    // 主界面只打印状态消息并切换 XYZ 颜色，采集和计算功能不受此状态影响。
    if (!message.isEmpty()) {
        appendLog(message);
    }

    if (state == TrackingState::Unknown) {
        return;
    }

    const bool lost = state == TrackingState::Lost;
    const QString coordinateStyle =
        lost
            ? QStringLiteral("font: 700 18pt \"Consolas\"; color: #d93025;")
            : QStringLiteral("font: 700 18pt \"Consolas\"; color: #005fb8;");
    ui->xValueLabel->setStyleSheet(coordinateStyle);
    ui->yValueLabel->setStyleSheet(coordinateStyle);
    ui->zValueLabel->setStyleSheet(coordinateStyle);
}

void MainWindow::showConnectedState(bool connected)
{
    ui->connectButton->setEnabled(!connected);
    ui->disconnectButton->setEnabled(connected);
    ui->startButton->setEnabled(connected && !m_client->isPolling());
    ui->stopButton->setEnabled(connected && m_client->isPolling());
    ui->readOnceButton->setEnabled(connected);
    refreshCirclePointTable();

    ui->automationStatusLabel->setText(
        connected ? QStringLiteral("Automation 已连接") : QStringLiteral("Automation 未连接"));
    ui->automationStatusLabel->setStyleSheet(
        connected
            ? QStringLiteral("color: #137333; font-weight: 600;")
            : QStringLiteral("color: #b3261e; font-weight: 600;"));

    if (!connected) {
        const QString coordinateStyle =
            QStringLiteral("font: 700 18pt \"Consolas\"; color: #005fb8;");
        ui->xValueLabel->setStyleSheet(coordinateStyle);
        ui->yValueLabel->setStyleSheet(coordinateStyle);
        ui->zValueLabel->setStyleSheet(coordinateStyle);
    }
}

void MainWindow::showPollingState(bool polling)
{
    ui->startButton->setEnabled(m_client->isConnected() && !polling);
    ui->stopButton->setEnabled(m_client->isConnected() && polling);
    ui->intervalSpinBox->setEnabled(!polling);

    statusBar()->showMessage(
        polling ? QStringLiteral("正在读取仪器坐标") : QStringLiteral("当前未读取坐标"));
}

void MainWindow::appendLog(const QString &message)
{
    const QString time = QDateTime::currentDateTime().toString(QStringLiteral("HH:mm:ss.zzz"));
    ui->logEdit->appendPlainText(QStringLiteral("[%1] %2").arg(time, message));
}

void MainWindow::showError(const QString &message)
{
    appendLog(QStringLiteral("错误：%1").arg(message));
    statusBar()->showMessage(message, 10000);
    QMessageBox::warning(this, QStringLiteral("PC-DMIS 访问失败"), message);
}

void MainWindow::refreshCirclePointTable()
{
    ui->circlePointsTable->setRowCount(
        static_cast<int>(m_circlePoints.size()));
    for (int row = 0;
         row < static_cast<int>(m_circlePoints.size()); ++row) {
        const GeometryPoint &point =
            m_circlePoints[static_cast<std::size_t>(row)];
        auto *indexItem = new QTableWidgetItem(
            QString::number(row + 1));
        indexItem->setTextAlignment(Qt::AlignCenter);
        ui->circlePointsTable->setItem(row, 0, indexItem);
        ui->circlePointsTable->setItem(row, 1, numberItem(point.x));
        ui->circlePointsTable->setItem(row, 2, numberItem(point.y));
        ui->circlePointsTable->setItem(row, 3, numberItem(point.z));
    }

    ui->circlePointCountLabel->setText(
        QStringLiteral("已采集：%1 点（至少 3 点，建议 6 点以上）")
            .arg(m_circlePoints.size()));
    const bool manualEnabled = !isRobotMeasurementActive();
    ui->captureCirclePointButton->setEnabled(
        manualEnabled && m_client->isConnected() &&
        !m_circleCapturePending);
    ui->calculateCircleButton->setEnabled(
        manualEnabled && m_circlePoints.size() >= 3);
    ui->deleteCirclePointButton->setEnabled(
        manualEnabled && !m_circlePoints.empty());
    ui->clearCirclePointsButton->setEnabled(
        manualEnabled &&
        (!m_circlePoints.empty() || !m_measurementResults.empty()));
    ui->coordinateModeComboBox->setEnabled(manualEnabled);
    ui->tcpZOffsetSpinBox->setEnabled(manualEnabled);
    ui->exportCircleResultsButton->setEnabled(
        manualEnabled && !m_measurementResults.empty());
}

void MainWindow::showCircleResult(const CircleFitResult &result)
{
    ui->circleResultTable->setRowCount(1);
    auto *indexItem = new QTableWidgetItem(QStringLiteral("1"));
    indexItem->setTextAlignment(Qt::AlignCenter);
    ui->circleResultTable->setItem(0, 0, indexItem);

    const std::array<double, 10> values{
        result.center.x, result.center.y, result.center.z,
        result.angleA, result.angleB, result.angleC,
        result.radius, result.planeRms,
        result.circleRms, result.maximumResidual
    };
    for (int column = 0;
         column < static_cast<int>(values.size()); ++column) {
        ui->circleResultTable->setItem(
            0, column + 1,
            numberItem(values[static_cast<std::size_t>(column)]));
    }

    ui->circleResultTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);
    ui->circleResultTable->horizontalHeader()->setStretchLastSection(false);
}

void MainWindow::applyTcpZOffset(CircleFitResult &result) const
{
    const double offset = ui->tcpZOffsetSpinBox->value();
    result.center.x -= offset * result.normal.x;
    result.center.y -= offset * result.normal.y;
    result.center.z -= offset * result.normal.z;
}

int MainWindow::appendCircleResult(
    int pointIndex, const CircleFitResult &result)
{
    const int row = ui->circleResultTable->rowCount();
    ui->circleResultTable->insertRow(row);

    auto *indexItem = new QTableWidgetItem(QString::number(pointIndex));
    indexItem->setTextAlignment(Qt::AlignCenter);
    ui->circleResultTable->setItem(row, 0, indexItem);

    const std::array<double, 10> values{
        result.center.x, result.center.y, result.center.z,
        result.angleA, result.angleB, result.angleC,
        result.radius, result.planeRms,
        result.circleRms, result.maximumResidual
    };
    for (int column = 0;
         column < static_cast<int>(values.size()); ++column) {
        ui->circleResultTable->setItem(
            row, column + 1,
            numberItem(values[static_cast<std::size_t>(column)]));
    }

    ui->circleResultTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);
    ui->circleResultTable->horizontalHeader()->setStretchLastSection(false);
    return row;
}

void MainWindow::markCircleResultWarning(int row)
{
    const QColor backgroundColor(QStringLiteral("#f8d7da"));
    const QColor foregroundColor(QStringLiteral("#b00020"));
    for (int column = 0;
         column < ui->circleResultTable->columnCount(); ++column) {
        QTableWidgetItem *item = ui->circleResultTable->item(row, column);
        if (item == nullptr) {
            continue;
        }
        item->setBackground(backgroundColor);
        item->setForeground(foregroundColor);
    }
}

void MainWindow::handleRobotBusinessRequest(
    quint64 requestToken, const QString &payload)
{
    static const QRegularExpression pointPattern(
        QStringLiteral(R"(^P([1-9]\d*)/([1-9]\d*)$)"));

    const QRegularExpressionMatch pointMatch =
        pointPattern.match(payload);
    if (pointMatch.hasMatch()) {
        bool pointOk = false;
        bool totalOk = false;
        const int pointIndex = pointMatch.captured(1).toInt(&pointOk);
        const int totalPoints = pointMatch.captured(2).toInt(&totalOk);
        if (!pointOk || !totalOk || pointIndex > totalPoints) {
            rejectRobotRequest(requestToken, payload,
                               QStringLiteral("P指令点位编号无效"));
            return;
        }

        handleRobotPointCommand(
            requestToken, payload, pointIndex, totalPoints);
        return;
    }

    if (payload == QStringLiteral("S")) {
        handleRobotSampleCommand(requestToken, payload);
        return;
    }

    if (payload.startsWith(QStringLiteral("C,"))) {
        const QStringList fields = payload.split(
            QLatin1Char(','), Qt::KeepEmptyParts);
        if (fields.size() != 7) {
            rejectRobotRequest(
                requestToken, payload,
                QStringLiteral("C指令必须包含点位编号和5个关节值"));
            return;
        }

        bool pointOk = false;
        const int pointIndex = fields.at(1).toInt(&pointOk);
        std::array<double, 5> joints{};
        bool jointsOk = true;
        for (int index = 0; index < 5; ++index) {
            bool valueOk = false;
            const double value = fields.at(index + 2).toDouble(&valueOk);
            if (!valueOk || !std::isfinite(value)) {
                jointsOk = false;
                break;
            }
            joints[static_cast<std::size_t>(index)] = value;
        }

        if (!pointOk || pointIndex <= 0 || !jointsOk) {
            rejectRobotRequest(
                requestToken, payload,
                QStringLiteral("C指令中的点位编号或关节值无效"));
            return;
        }

        handleRobotCalculateCommand(
            requestToken, payload, pointIndex, joints);
        return;
    }

    rejectRobotRequest(
        requestToken, payload,
        QStringLiteral("不支持的payload，仅接受P、S或C指令"));
}

void MainWindow::handleRobotPointCommand(
    quint64 requestToken, const QString &payload,
    int pointIndex, int totalPoints)
{
    if (!m_client->isConnected()) {
        rejectRobotRequest(requestToken, payload,
                           QStringLiteral("PC-DMIS尚未连接"));
        return;
    }
    if (!m_hasTrackerOrigin) {
        rejectRobotRequest(
            requestToken, payload,
            QStringLiteral("尚未取得激光跟踪仪在当前坐标系中的位置"));
        return;
    }

    if (pointIndex == 1) {
        const bool canStartNewTask =
            m_robotMeasurementState == RobotMeasurementState::Idle ||
            m_robotMeasurementState == RobotMeasurementState::Completed ||
            m_robotMeasurementState == RobotMeasurementState::Error;
        if (!canStartNewTask || m_circleCapturePending) {
            rejectRobotRequest(
                requestToken, payload,
                QStringLiteral("当前机器人测量任务尚未结束，不能重新接收P1"));
            return;
        }
        resetRobotMeasurementTask(totalPoints);
    } else {
        if (m_robotMeasurementState !=
                RobotMeasurementState::WaitingForPoint ||
            totalPoints != m_robotTotalPoints ||
            pointIndex != m_lastCompletedRobotPoint + 1) {
            rejectRobotRequest(
                requestToken, payload,
                QStringLiteral("P指令顺序错误或总点数与当前任务不一致"));
            return;
        }
    }

    m_robotCurrentPoint = pointIndex;
    clearCurrentCirclePoints();
    appendLog(QStringLiteral("机器人到达点位 P%1/%2，开始首次采点。")
                  .arg(pointIndex)
                  .arg(totalPoints));
    beginRobotCircleCapture(requestToken, payload);
}

void MainWindow::handleRobotSampleCommand(
    quint64 requestToken, const QString &payload)
{
    if (m_robotMeasurementState !=
        RobotMeasurementState::ReadyForCommand) {
        rejectRobotRequest(
            requestToken, payload,
            QStringLiteral("当前未处于可追加采点状态"));
        return;
    }

    beginRobotCircleCapture(requestToken, payload);
}

void MainWindow::handleRobotCalculateCommand(
    quint64 requestToken, const QString &payload,
    int pointIndex, const std::array<double, 5> &joints)
{
    if (m_robotMeasurementState !=
            RobotMeasurementState::ReadyForCommand ||
        pointIndex != m_robotCurrentPoint) {
        rejectRobotRequest(
            requestToken, payload,
            QStringLiteral("C指令点位与当前采集点位不一致，或当前不可计算"));
        return;
    }
    if (!m_hasTrackerOrigin) {
        m_robotMeasurementState = RobotMeasurementState::Error;
        refreshCirclePointTable();
        rejectRobotRequest(
            requestToken, payload,
            QStringLiteral("尚未取得激光跟踪仪在当前坐标系中的位置"));
        return;
    }

    CircleFitResult result =
        GeometryCalculator::fitCircle(m_circlePoints, m_trackerOrigin);
    if (!result.success) {
        m_robotMeasurementState = RobotMeasurementState::Error;
        refreshCirclePointTable();
        rejectRobotRequest(requestToken, payload,
                           QStringLiteral("圆拟合失败：%1")
                               .arg(result.errorMessage));
        return;
    }

    // 手动计算和TCP计算统一使用界面中的靶球Z偏移。
    applyTcpZOffset(result);

    RobotTcpPose tcpPose;
    QString kinematicsError;
    if (!m_robotKinematics.forward5Axis(
            joints, tcpPose, kinematicsError)) {
        m_robotMeasurementState = RobotMeasurementState::Error;
        refreshCirclePointTable();
        rejectRobotRequest(
            requestToken, payload,
            QStringLiteral("机器人正解失败：%1")
                .arg(kinematicsError));
        return;
    }

    const double differenceX = result.center.x - tcpPose.x;
    const double differenceY = result.center.y - tcpPose.y;
    const double differenceZ = result.center.z - tcpPose.z;
    const double centerDistance = std::sqrt(
        differenceX * differenceX +
        differenceY * differenceY +
        differenceZ * differenceZ);
    const bool positionWarning =
        centerDistance > kTcpCenterWarningDistanceMm;

    MeasurementResultRecord record;
    record.pointIndex = pointIndex;
    record.totalPoints = m_robotTotalPoints;
    record.sampleCount = static_cast<int>(m_circlePoints.size());
    record.joints = joints;
    record.circle = result;
    record.completedAt = QDateTime::currentDateTime();
    m_measurementResults.push_back(record);
    const int resultRow = appendCircleResult(pointIndex, result);
    if (positionWarning) {
        markCircleResultWarning(resultRow);
        appendLog(QStringLiteral(
                      "警告：点位 P%1 正解TCP=(%2, %3, %4)，"
                      "拟合圆心=(%5, %6, %7)，"
                      "XYZ差值=(%8, %9, %10)，空间距离=%11 mm，超过10 mm。")
                      .arg(pointIndex)
                      .arg(tcpPose.x, 0, 'f', 6)
                      .arg(tcpPose.y, 0, 'f', 6)
                      .arg(tcpPose.z, 0, 'f', 6)
                      .arg(result.center.x, 0, 'f', 6)
                      .arg(result.center.y, 0, 'f', 6)
                      .arg(result.center.z, 0, 'f', 6)
                      .arg(differenceX, 0, 'f', 6)
                      .arg(differenceY, 0, 'f', 6)
                      .arg(differenceZ, 0, 'f', 6)
                      .arg(centerDistance, 0, 'f', 6));
    }

    appendLog(QStringLiteral(
                  "点位 P%1/%2 计算完成，共 %3 个采样点；"
                  "5个关节值已保存到结果记录中。")
                  .arg(pointIndex)
                  .arg(m_robotTotalPoints)
                  .arg(record.sampleCount));

    m_lastCompletedRobotPoint = pointIndex;
    m_robotCurrentPoint = 0;
    clearCurrentCirclePoints();
    m_robotMeasurementState =
        pointIndex == m_robotTotalPoints
            ? RobotMeasurementState::Completed
            : RobotMeasurementState::WaitingForPoint;
    refreshCirclePointTable();

    if (m_robotMeasurementState == RobotMeasurementState::Completed) {
        appendLog(QStringLiteral("机器人测量任务已完成，共累计 %1 条结果。")
                      .arg(m_measurementResults.size()));
    }
    completeRobotRequest(requestToken);
}

void MainWindow::beginRobotCircleCapture(
    quint64 requestToken, const QString &payload)
{
    if (!m_client->isConnected()) {
        m_robotMeasurementState = RobotMeasurementState::Error;
        refreshCirclePointTable();
        rejectRobotRequest(requestToken, payload,
                           QStringLiteral("PC-DMIS尚未连接"));
        return;
    }
    if (!m_hasTrackerOrigin) {
        m_robotMeasurementState = RobotMeasurementState::Error;
        refreshCirclePointTable();
        rejectRobotRequest(
            requestToken, payload,
            QStringLiteral("尚未取得激光跟踪仪在当前坐标系中的位置"));
        return;
    }
    if (m_circleCapturePending) {
        rejectRobotRequest(requestToken, payload,
                           QStringLiteral("上一条采点请求尚未完成"));
        return;
    }

    m_robotMeasurementState = RobotMeasurementState::Sampling;
    m_circleCapturePending = true;
    m_circleCaptureSource = CircleCaptureSource::Robot;
    m_pendingRobotRequestToken = requestToken;
    m_pendingRobotPayload = payload;
    m_pendingCircleCaptureId = m_nextCoordinateRequestId++;
    refreshCirclePointTable();
    statusBar()->showMessage(QStringLiteral("正在执行机器人圆周采点..."));
    m_client->requestCoordinateSample(m_pendingCircleCaptureId);
}

void MainWindow::completeRobotRequest(quint64 requestToken)
{
    emit completeTcpBusinessRequestRequested(
        requestToken, QStringLiteral("ok"));
}

void MainWindow::rejectRobotRequest(
    quint64 requestToken, const QString &payload, const QString &reason)
{
    appendLog(QStringLiteral(
                  "机器人业务请求不回复：payload=\"%1\"，原因：%2。")
                  .arg(payload, reason));
    statusBar()->showMessage(
        QStringLiteral("机器人业务处理失败：%1").arg(reason), 10000);
    emit discardTcpBusinessRequestRequested(requestToken);
}

void MainWindow::clearCurrentCirclePoints()
{
    m_circlePoints.clear();
    m_circlePointCoordinateMode = -1;
    refreshCirclePointTable();
}

void MainWindow::resetRobotMeasurementTask(int totalPoints)
{
    m_measurementResults.clear();
    m_robotCurrentPoint = 0;
    m_robotTotalPoints = totalPoints;
    m_lastCompletedRobotPoint = 0;
    m_pendingRobotRequestToken = 0;
    m_pendingRobotPayload.clear();
    m_robotMeasurementState = RobotMeasurementState::WaitingForPoint;
    ui->circleResultTable->setRowCount(0);
    appendLog(QStringLiteral("开始新的机器人测量任务，总点数：%1。")
                  .arg(totalPoints));
}

bool MainWindow::isRobotMeasurementActive() const
{
    return m_robotMeasurementState == RobotMeasurementState::WaitingForPoint ||
           m_robotMeasurementState == RobotMeasurementState::Sampling ||
           m_robotMeasurementState == RobotMeasurementState::ReadyForCommand;
}

QString MainWindow::formatCsvNumber(double value)
{
    QString text = QString::number(value, 'f', 6);
    while (text.contains(QChar('.')) && text.endsWith(QChar('0'))) {
        text.chop(1);
    }
    if (text.endsWith(QChar('.'))) {
        text.chop(1);
    }
    return text == QStringLiteral("-0") ? QStringLiteral("0") : text;
}
