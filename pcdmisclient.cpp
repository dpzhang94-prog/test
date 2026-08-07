#include "pcdmisclient.h"

#include "pcdmisworker.h"

#include <QMetaObject>
#include <QMetaType>
#include <QThread>

PcdmisClient::PcdmisClient(QObject *parent)
    : QObject(parent),
      m_workerThread(new QThread(this)),
      m_worker(new PcdmisWorker)
{
    // 自定义状态需要注册后才能通过队列连接安全地传递到主线程。
    qRegisterMetaType<TrackingState>("TrackingState");

    // Worker 没有主线程父对象，移动后由工作线程负责其事件和 COM 生命周期。
    m_worker->moveToThread(m_workerThread);
    connect(m_workerThread, &QThread::started,
            m_worker, &PcdmisWorker::initialize);
    connect(m_workerThread, &QThread::finished,
            m_worker, &QObject::deleteLater);

    // 主线程请求全部使用队列连接，禁止普通函数调用跨越线程边界。
    connect(this, &PcdmisClient::connectRequested,
            m_worker, &PcdmisWorker::connectToPcdmis,
            Qt::QueuedConnection);
    connect(this, &PcdmisClient::disconnectRequested,
            m_worker, &PcdmisWorker::disconnectFromPcdmis,
            Qt::QueuedConnection);
    connect(this, &PcdmisClient::coordinateModeRequested,
            m_worker, &PcdmisWorker::setCoordinateMode,
            Qt::QueuedConnection);
    connect(this, &PcdmisClient::pollingEnabledRequested,
            m_worker, &PcdmisWorker::setPollingEnabled,
            Qt::QueuedConnection);
    connect(this, &PcdmisClient::pollingIntervalRequested,
            m_worker, &PcdmisWorker::setPollingInterval,
            Qt::QueuedConnection);
    connect(this, &PcdmisClient::readOnceRequested,
            m_worker, &PcdmisWorker::readOnce,
            Qt::QueuedConnection);
    connect(this, &PcdmisClient::coordinateSampleRequested,
            m_worker, &PcdmisWorker::requestCoordinateSample,
            Qt::QueuedConnection);
    connect(this, &PcdmisClient::trackerOriginRefreshRequested,
            m_worker, &PcdmisWorker::refreshAlignedTrackerOrigin,
            Qt::QueuedConnection);

    // Worker 返回的数据进入主线程后，先更新门面缓存，再通知界面。
    connect(m_worker, &PcdmisWorker::connectedChanged,
            this, &PcdmisClient::handleWorkerConnectedChanged,
            Qt::QueuedConnection);
    connect(m_worker, &PcdmisWorker::pollingChanged,
            this, &PcdmisClient::handleWorkerPollingChanged,
            Qt::QueuedConnection);
    connect(m_worker, &PcdmisWorker::coordinateReceived,
            this, &PcdmisClient::handleWorkerCoordinate,
            Qt::QueuedConnection);
    connect(m_worker, &PcdmisWorker::coordinateSampleFinished,
            this, &PcdmisClient::coordinateSampleFinished,
            Qt::QueuedConnection);
    connect(m_worker, &PcdmisWorker::trackerOriginChanged,
            this, &PcdmisClient::handleWorkerTrackerOrigin,
            Qt::QueuedConnection);
    connect(m_worker, &PcdmisWorker::trackerOriginRefreshFinished,
            this, &PcdmisClient::handleWorkerTrackerOriginRefreshFinished,
            Qt::QueuedConnection);
    connect(m_worker, &PcdmisWorker::trackingStateChanged,
            this, &PcdmisClient::trackingStateChanged,
            Qt::QueuedConnection);
    connect(m_worker, &PcdmisWorker::measurementValidityChanged,
            this, &PcdmisClient::measurementValidityChanged,
            Qt::QueuedConnection);
    connect(m_worker, &PcdmisWorker::logMessage,
            this, &PcdmisClient::logMessage,
            Qt::QueuedConnection);
    connect(m_worker, &PcdmisWorker::errorOccurred,
            this, &PcdmisClient::errorOccurred,
            Qt::QueuedConnection);

    m_workerThread->start();
}

PcdmisClient::~PcdmisClient()
{
    if (m_workerThread->isRunning() && m_worker != nullptr) {
        // 退出时允许短暂阻塞主线程，确保 QAxObject 在所属线程内释放完毕。
        QMetaObject::invokeMethod(
            m_worker,
            [worker = m_worker]() { worker->shutdown(); },
            Qt::BlockingQueuedConnection);
        m_workerThread->quit();
        m_workerThread->wait();
    }
    m_worker = nullptr;
}

bool PcdmisClient::isConnected() const
{
    return m_connected;
}

bool PcdmisClient::isPolling() const
{
    return m_polling;
}

int PcdmisClient::pollingInterval() const
{
    return m_pollingIntervalMs;
}

bool PcdmisClient::hasAlignedTrackerOrigin() const
{
    return m_connected && m_alignedTrackerOriginValid;
}

std::array<double, 3> PcdmisClient::alignedTrackerOrigin() const
{
    return m_alignedTrackerOrigin;
}

void PcdmisClient::connectToPcdmis(bool makeVisible)
{
    emit connectRequested(makeVisible);
}

void PcdmisClient::disconnectFromPcdmis()
{
    emit disconnectRequested();
}

void PcdmisClient::setCoordinateMode(int modeIndex)
{
    m_coordinateMode = (modeIndex == 1) ? 1 : 0;
    emit coordinateModeRequested(m_coordinateMode);
}

void PcdmisClient::setPollingEnabled(bool enabled)
{
    emit pollingEnabledRequested(enabled);
}

void PcdmisClient::setPollingInterval(int milliseconds)
{
    m_pollingIntervalMs = qBound(20, milliseconds, 5000);
    emit pollingIntervalRequested(m_pollingIntervalMs);
}

void PcdmisClient::readOnce()
{
    emit readOnceRequested();
}

void PcdmisClient::requestCoordinateSample(quint64 requestId)
{
    emit coordinateSampleRequested(requestId);
}

void PcdmisClient::refreshAlignedTrackerOrigin()
{
    emit trackerOriginRefreshRequested();
}

void PcdmisClient::handleWorkerConnectedChanged(bool connected)
{
    m_connected = connected;
    if (!connected) {
        m_polling = false;
        m_alignedTrackerOriginValid = false;
        m_alignedTrackerOrigin.fill(0.0);
    }
    emit connectedChanged(connected);
}

void PcdmisClient::handleWorkerPollingChanged(bool polling)
{
    m_polling = polling;
    emit pollingChanged(polling);
}

void PcdmisClient::handleWorkerCoordinate(double x, double y, double z,
                                          int coordinateMode)
{
    // 模式切换时队列中可能仍有上一模式的结果，不能让旧坐标重新显示。
    if (coordinateMode != m_coordinateMode) {
        return;
    }
    emit coordinateReceived(x, y, z);
}

void PcdmisClient::handleWorkerTrackerOrigin(double x, double y, double z,
                                             int coordinateMode)
{
    // 对齐原点要始终缓存，供 TestPoints 查询；但只有它与主界面当前
    // 坐标模式一致时，才作为当前坐标系原点向 UI 广播。
    if (coordinateMode == 1) {
        m_alignedTrackerOrigin = {x, y, z};
        m_alignedTrackerOriginValid = true;
    }
    if (coordinateMode != m_coordinateMode) {
        return;
    }
    emit trackerOriginChanged(x, y, z);
}

void PcdmisClient::handleWorkerTrackerOriginRefreshFinished(
    bool success, double x, double y, double z,
    const QString &errorMessage)
{
    if (success) {
        m_alignedTrackerOrigin = {x, y, z};
        m_alignedTrackerOriginValid = true;
    }
    emit trackerOriginRefreshFinished(
        success, x, y, z, errorMessage);
}
