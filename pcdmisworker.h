#pragma once

#include "trackingstate.h"

#include <array>

#include <QElapsedTimer>
#include <QObject>

class QAxObject;
class QTimer;

// PC-DMIS 工作对象。
//
// 本类只在专用工作线程中使用。所有 QAxObject、COM 调用和轮询定时器
// 都归该线程所有，主线程不得直接调用这里的函数。
class PcdmisWorker final : public QObject
{
    Q_OBJECT

public:
    explicit PcdmisWorker(QObject *parent = nullptr);
    ~PcdmisWorker() override;

public slots:
    void initialize();
    void connectToPcdmis(bool makeVisible = true);
    void disconnectFromPcdmis();
    void setCoordinateMode(int modeIndex);
    void setPollingEnabled(bool enabled);
    void setPollingInterval(int milliseconds);
    void readOnce();
    void requestCoordinateSample(quint64 requestId);
    void refreshAlignedTrackerOrigin();
    void shutdown();

signals:
    void connectedChanged(bool connected);
    void pollingChanged(bool polling);
    void coordinateReceived(double x, double y, double z, int coordinateMode);
    void coordinateSampleFinished(quint64 requestId, bool success,
                                  double x, double y, double z,
                                  int coordinateMode,
                                  const QString &errorMessage);
    void trackerOriginChanged(double x, double y, double z,
                              int coordinateMode);
    void trackerOriginRefreshFinished(bool success,
                                      double x, double y, double z,
                                      const QString &errorMessage);
    void trackingStateChanged(TrackingState state,
                              const QString &message);
    void measurementValidityChanged(bool valid, const QString &reason);
    void logMessage(const QString &message);
    void errorOccurred(const QString &message);

private slots:
    void pollProbePosition();
    void onMachineReadoutExt(double x, double y, double z);
    void onMachineEvent(const QString &name, int argumentCount,
                        void *arguments);
    void onMachineError(const QString &message, int errorType);
    void onComException(int code, const QString &source,
                        const QString &description, const QString &help);

private:
    bool isConnected() const;
    bool isPolling() const;
    bool readCurrentCoordinate(double &x, double &y, double &z,
                               QString &errorMessage,
                               std::array<double, 3> *rawCoordinate = nullptr);
    void handleContinuousReadFailure(const QString &errorMessage);
    void updateTrackingState(const std::array<double, 3> &rawCoordinate);
    void setTrackingState(TrackingState state, const QString &message);
    void resetTrackingDetection();
    void noteReadoutHeartbeat();
    void checkReadoutHeartbeat();
    void setReflectorAvailability(bool available, const QString &reason);
    QAxObject *selectMachine(QAxObject *machines);
    QAxObject *machineAt(QAxObject *machines, int index) const;
    bool refreshAlignmentMatrix(bool logSuccess);
    bool transformPoint(double machineX, double machineY, double machineZ,
                        double &partX, double &partY, double &partZ);
    void releaseAlignmentObjects();
    void releaseComObjects();

    QAxObject *m_application = nullptr;
    QAxObject *m_machines = nullptr;
    QAxObject *m_activePartProgram = nullptr;
    QAxObject *m_machine = nullptr;
    QAxObject *m_commands = nullptr;
    QAxObject *m_currentAlignmentCommand = nullptr;
    QAxObject *m_alignmentCommand = nullptr;
    QAxObject *m_machineToPartMatrix = nullptr;
    QTimer *m_pollTimer = nullptr;
    bool m_comInitialized = false;
    int m_pollingIntervalMs = 100;
    int m_consecutiveReadFailures = 0;
    int m_coordinateMode = 0;
    int m_alignmentRefreshCounter = 0;
    bool m_matrixIdentityKnown = false;
    bool m_matrixIsIdentity = false;
    bool m_matrixValuesValid = false;
    bool m_loggedTransformSuccess = false;
    TrackingState m_trackingState = TrackingState::Unknown;
    int m_identicalCoordinateCount = 0;
    bool m_lastRawCoordinateValid = false;
    std::array<double, 3> m_lastRawCoordinate{};
    enum class ReflectorState {
        Unknown,
        Available,
        Unavailable
    };
    ReflectorState m_reflectorState = ReflectorState::Unknown;
    QElapsedTimer m_readoutHeartbeatTimer;
    bool m_readoutHeartbeatSeen = false;
    bool m_missingHeartbeatWarningLogged = false;
    std::array<double, 12> m_matrixValues{};
    std::array<double, 3> m_alignedTrackerOrigin{};
    bool m_alignedTrackerOriginValid = false;
    QString m_lastAlignmentDescription;
};
