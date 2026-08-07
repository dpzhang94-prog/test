#pragma once

#include "geometrycalculator.h"
#include "trackingstate.h"

#include <QMainWindow>

#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PcdmisClient;
class QThread;
class TcpServerWorker;

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void connectPcdmis();
    void disconnectPcdmis();
    void startPolling();
    void stopPolling();
    void startTcpServer();
    void stopTcpServer();
    void openTestPointsDialog();
    void captureCirclePoint();
    void deleteSelectedCirclePoints();
    void clearCirclePoints();
    void calculateCircle();
    void showCoordinate(double x, double y, double z);
    void finishCirclePointCapture(quint64 requestId, bool success,
                                  double x, double y, double z,
                                  int coordinateMode,
                                  const QString &errorMessage);
    void setTrackerOrigin(double x, double y, double z);
    void showTrackingState(TrackingState state, const QString &message);
    void showConnectedState(bool connected);
    void showPollingState(bool polling);
    void showTcpServerState(bool running, const QString &listenAddress);
    void appendLog(const QString &message);
    void showError(const QString &message);

signals:
    void startTcpServerRequested();
    void stopTcpServerRequested();

private:
    void refreshCirclePointTable();
    void showCircleResult(const CircleFitResult &result);

    Ui::MainWindow *ui = nullptr;
    PcdmisClient *m_client = nullptr;
    QThread *m_tcpThread = nullptr;
    TcpServerWorker *m_tcpWorker = nullptr;
    std::vector<GeometryPoint> m_circlePoints;
    GeometryPoint m_trackerOrigin;
    quint64 m_nextCoordinateRequestId = 1;
    quint64 m_pendingCircleCaptureId = 0;
    int m_circlePointCoordinateMode = -1;
    bool m_hasTrackerOrigin = false;
    bool m_circleCapturePending = false;
};
