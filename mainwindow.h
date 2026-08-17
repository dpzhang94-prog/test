#pragma once

#include "geometrycalculator.h"
#include "robotkinematics.h"
#include "trackingstate.h"

#include <QDateTime>
#include <QMainWindow>

#include <array>
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
    void exportCircleResults();
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

    // 解析并分发机器人发送的P、S、C业务指令。
    void handleRobotBusinessRequest(quint64 requestToken,
                                    const QString &payload);
    void appendLog(const QString &message);
    void showError(const QString &message);

signals:
    void startTcpServerRequested();
    void stopTcpServerRequested();
    void completeTcpBusinessRequestRequested(quint64 requestToken,
                                             const QString &data);
    void discardTcpBusinessRequestRequested(quint64 requestToken);

private:
    enum class CircleCaptureSource
    {
        None,
        Manual,
        Robot
    };

    enum class RobotMeasurementState
    {
        Idle,
        WaitingForPoint,
        Sampling,
        ReadyForCommand,
        Completed,
        Error
    };

    struct MeasurementResultRecord
    {
        int pointIndex = 0;
        int totalPoints = 0;
        int sampleCount = 0;
        std::array<double, 5> joints{};
        CircleFitResult circle;
        QDateTime completedAt;
    };

    // 刷新采集点表格和相关按钮状态。
    void refreshCirclePointTable();

    // 显示单次手动计算结果。
    void showCircleResult(const CircleFitResult &result);

    // 沿拟合结果自身Z轴的负方向修正圆心位置。
    void applyTcpZOffset(CircleFitResult &result) const;

    // 将一条机器人计算结果追加到结果表格。
    int appendCircleResult(int pointIndex, const CircleFitResult &result);

    // 将指定结果行设置为TCP位置偏差警告样式。
    void markCircleResultWarning(int row);

    // 处理P指令，建立或推进机器人批量测量任务。
    void handleRobotPointCommand(quint64 requestToken,
                                 const QString &payload,
                                 int pointIndex, int totalPoints);

    // 处理S指令，追加一个当前点位的圆周采样点。
    void handleRobotSampleCommand(quint64 requestToken,
                                  const QString &payload);

    // 处理C指令，计算并保存当前点位结果。
    void handleRobotCalculateCommand(
        quint64 requestToken, const QString &payload,
        int pointIndex, const std::array<double, 5> &joints);

    // 向PC-DMIS发起一次由机器人指令触发的坐标采样。
    void beginRobotCircleCapture(quint64 requestToken,
                                 const QString &payload);

    // 业务成功时通知TCP线程回复ACK。
    void completeRobotRequest(quint64 requestToken);

    // 业务失败时仅记录日志并丢弃请求，不回复机器人。
    void rejectRobotRequest(quint64 requestToken,
                            const QString &payload,
                            const QString &reason);

    // 清空当前点位采样，不影响已累计的计算结果。
    void clearCurrentCirclePoints();

    // 开始一个新的机器人批量测量任务。
    void resetRobotMeasurementTask(int totalPoints);

    // 返回机器人任务是否正在占用采集与计算控件。
    bool isRobotMeasurementActive() const;

    // 将数值格式化为CSV使用的简洁文本。
    static QString formatCsvNumber(double value);

    Ui::MainWindow *ui = nullptr;
    PcdmisClient *m_client = nullptr;
    QThread *m_tcpThread = nullptr;
    TcpServerWorker *m_tcpWorker = nullptr;
    RobotKinematics m_robotKinematics;
    std::vector<GeometryPoint> m_circlePoints;
    std::vector<MeasurementResultRecord> m_measurementResults;
    GeometryPoint m_trackerOrigin;
    quint64 m_nextCoordinateRequestId = 1;
    quint64 m_pendingCircleCaptureId = 0;
    int m_circlePointCoordinateMode = -1;
    int m_robotCurrentPoint = 0;
    int m_robotTotalPoints = 0;
    int m_lastCompletedRobotPoint = 0;
    quint64 m_pendingRobotRequestToken = 0;
    QString m_pendingRobotPayload;
    CircleCaptureSource m_circleCaptureSource = CircleCaptureSource::None;
    RobotMeasurementState m_robotMeasurementState =
        RobotMeasurementState::Idle;
    bool m_hasTrackerOrigin = false;
    bool m_circleCapturePending = false;
};
