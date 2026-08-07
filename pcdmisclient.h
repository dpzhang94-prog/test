#pragma once

#include "trackingstate.h"

#include <array>

#include <QObject>

class PcdmisWorker;
class QThread;

// 主线程中的 PC-DMIS 门面。
//
// MainWindow 和 TestPoints 只与本类交互。本类不访问 COM，而是把请求排入
// PcdmisWorker 所在的工作线程，并在主线程缓存少量界面状态。
class PcdmisClient final : public QObject
{
    Q_OBJECT

public:
    explicit PcdmisClient(QObject *parent = nullptr);
    ~PcdmisClient() override;

    bool isConnected() const;
    bool isPolling() const;
    int pollingInterval() const;
    bool hasAlignedTrackerOrigin() const;
    std::array<double, 3> alignedTrackerOrigin() const;

public slots:
    void connectToPcdmis(bool makeVisible = true);
    void disconnectFromPcdmis();
    void setCoordinateMode(int modeIndex);
    void setPollingEnabled(bool enabled);
    void setPollingInterval(int milliseconds);
    void readOnce();
    void requestCoordinateSample(quint64 requestId);
    void refreshAlignedTrackerOrigin();

signals:
    // 对 UI 保持稳定的公开信号。
    void connectedChanged(bool connected);
    void pollingChanged(bool polling);
    void coordinateReceived(double x, double y, double z);
    void coordinateSampleFinished(quint64 requestId, bool success,
                                  double x, double y, double z,
                                  int coordinateMode,
                                  const QString &errorMessage);
    void trackerOriginChanged(double x, double y, double z);
    void trackerOriginRefreshFinished(bool success,
                                      double x, double y, double z,
                                      const QString &errorMessage);
    void trackingStateChanged(TrackingState state,
                              const QString &message);
    void measurementValidityChanged(bool valid, const QString &reason);
    void logMessage(const QString &message);
    void errorOccurred(const QString &message);

    // 以下信号只用于把主线程请求安全地投递到工作线程。
    void connectRequested(bool makeVisible);
    void disconnectRequested();
    void coordinateModeRequested(int modeIndex);
    void pollingEnabledRequested(bool enabled);
    void pollingIntervalRequested(int milliseconds);
    void readOnceRequested();
    void coordinateSampleRequested(quint64 requestId);
    void trackerOriginRefreshRequested();

private slots:
    void handleWorkerConnectedChanged(bool connected);
    void handleWorkerPollingChanged(bool polling);
    void handleWorkerCoordinate(double x, double y, double z,
                                int coordinateMode);
    void handleWorkerTrackerOrigin(double x, double y, double z,
                                   int coordinateMode);
    void handleWorkerTrackerOriginRefreshFinished(
        bool success, double x, double y, double z,
        const QString &errorMessage);

private:
    QThread *m_workerThread = nullptr;
    PcdmisWorker *m_worker = nullptr;

    // 这些字段只在主线程读写，供 UI 同步查询，不需要加锁。
    bool m_connected = false;
    bool m_polling = false;
    int m_pollingIntervalMs = 100;
    int m_coordinateMode = 0;
    std::array<double, 3> m_alignedTrackerOrigin{};
    bool m_alignedTrackerOriginValid = false;
};
