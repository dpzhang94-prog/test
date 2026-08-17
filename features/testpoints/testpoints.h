#ifndef TESTPOINTS_H
#define TESTPOINTS_H

// 必须在包含 VTK 头文件前定义，避免 Windows 宏与 VTK 冲突。
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <QDialog>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#include "robotkinematics.h"

class vtkActor;
class vtkAxesActor;
class vtkRenderer;
class vtkSphereSource;
class vtkUnsignedCharArray;
class PcdmisClient;

namespace Ui {
class TestPoints;
}

class TestPoints : public QDialog
{
    Q_OBJECT

public:
    explicit TestPoints(PcdmisClient *pcdmisClient,
                        QWidget *parent = nullptr);
    ~TestPoints();

private slots:
    void on_pushButton_Confirm_clicked();
    void on_lineEdit_count_editingFinished();
    void refreshTrackerPosition();
    void handleTrackerOriginRefreshFinished(
        bool success, double x, double y, double z,
        const QString &errorMessage);
    void useTestTrackerPosition();
    void previewTrackerVisibility();
    void exportPreviewRetainedPoses();
    // 打开自定义加工文件面板并按设置生成新的 JBR 文件。
    void customizeMachiningFile();


private:
    Ui::TestPoints *ui;

    // 保存 STL 模型及其可视化对象。
    QString m_stlFilePath;
    vtkSmartPointer<vtkPolyData> m_stlPolyData;
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkActor> m_modelActor;
    vtkSmartPointer<vtkActor> m_centerActor;
    vtkSmartPointer<vtkAxesActor> m_axesActor;
    vtkSmartPointer<vtkSphereSource> m_centerSource;
    vtkSmartPointer<vtkUnsignedCharArray> m_modelCellColors;
    vtkSmartPointer<vtkSphereSource> m_trackerSource;
    vtkSmartPointer<vtkSphereSource> m_trackerRangeSource;
    vtkSmartPointer<vtkSphereSource> m_trackerInnerRangeSource;
    vtkSmartPointer<vtkActor> m_trackerActor;
    vtkSmartPointer<vtkActor> m_trackerRangeActor;
    vtkSmartPointer<vtkActor> m_trackerInnerRangeActor;
    vtkSmartPointer<vtkActor> m_visibilityPointsActor;
    vtkSmartPointer<vtkPolyData> m_visibilityPointsPolyData;
    double m_stlBounds[6] = {};
    double m_defaultRegionCenter[3] = {};
    double m_regionCenter[3] = {};
    double m_regionHalfLengths[3] = {};
    double m_regionThreshold = 0.0;
    bool m_regionCenterValid = false;

    // 保存公共正解计算对象，供测试点过滤重复使用。
    RobotKinematics m_robotKinematics;
    PcdmisClient *m_pcdmisClient = nullptr;
    double m_trackerOrigin[3] = {};
    bool m_trackerOriginValid = false;
    bool m_trackerOriginIsSimulated = false;
    bool m_trackerRefreshPending = false;
    QVector<QVector<double>> m_previewRetainedJointPoints;

    // 表示正解得到的 TCP 空间坐标。
    struct Point3D {
        double x;
        double y;
        double z;
    };

    struct Pose5D {
        Point3D position;
        double rx;
        double ry;
    };

    // 初始化 STL 三维显示窗口、扩散中心标记和模型坐标轴。
    void initializeStlView();

    // 打开文件选择框并加载 STL 模型。
    void chooseStlModel();

    // 将扩散中心恢复到自动计算的位置和默认范围。
    void resetRegion();

    // 将三维相机恢复到完整模型视角。
    void resetCamera();

    // 根据扩散范围和中心滑动条更新模型局部颜色。
    void updateRegion();

    // 计算并验证模型内部的默认扩散中心。
    Point3D calculateDefaultRegionCenter();

    // 计算点相对于当前扩散中心的归一化距离。
    double normalizedRegionDistance(const Point3D& point) const;

    // 使用打乱后的拉丁超立方在关节范围内生成指定数量的测试点。
    QVector<QVector<double>> generateAllTestPoints(
        const double j_min[6], const double j_max[6],
        const QVector<int>& validJoints, int count,
        bool allowDecimal);

    // 删除关节值完全相同的重复测试点。
    QVector<QVector<double>> removeDuplicatePoints(
        const QVector<QVector<double>>& allPoints);

    // 读取 STL 模型并更新三维显示。
    bool loadSTLModel(const QString& filePath);

    // 将关节值正解为 TCP 坐标，并返回计算是否成功。
    bool forwardKinematics(const QVector<double>& jointValues,
                           Point3D& tcpPosition);

    // 将关节值正解为 TCP 的位置和两轴姿态。
    bool forwardKinematicsPose(const QVector<double>& jointValues,
                               Pose5D& tcpPose);

    // 判断 TCP 点是否位于原始 STL 封闭空间内。
    bool isPointInsideSTL(const Point3D& point);

    // 判断 TCP 点是否位于当前三维扩散区域内。
    bool isPointInsideSelectedRegion(const Point3D& point) const;

    // 仅保留同时位于 STL 内部和可视化选区内的测试点。
    QVector<QVector<double>> filterUnreachablePoints(
        const QVector<QVector<double>>& allPoints, int& filteredCount);

    // 从当前界面参数生成去重后的候选关节点。
    bool generateCandidatePointsFromUi(
        QVector<QVector<double>>& uniquePoints,
        int& generatedCount, QString& errorMessage);

    // 保持五轴正解位姿，检查独立主轴 J6 带动靶球旋转一周时是否始终可见。
    bool isVisibleForFullRotation(
        const QVector<double>& jointValues);

    // 检查靶球相对 TCP 的安装参数是否足以执行 J6 整周计算。
    bool validateReflectorInstallation(QString& errorMessage) const;

    // 仅保留整周所有检查角度都满足距离和入射角的点位。
    QVector<QVector<double>> filterTrackerVisiblePoints(
        const QVector<QVector<double>>& allPoints,
        int& filteredCount);

    // 更新跟踪仪、测量范围和筛选结果的三维显示。
    void updateTrackerVisualization();
    void updateVisibilityPreview(
        const QVector<Point3D>& retainedPositions);
    void updateTrackerUiState();

    // 将测试点写入 TXT 文件。
    void generateTXTFile(const QString& fileName,
                         const QVector<QVector<double>>& allPoints);

    // 将测试点写入 CSV 文件。
    void generateCSVFile(const QString& baseFileName,
                         const QVector<QVector<double>>& allPoints);

    // 将测试点写入机器人 JBR 文件。
    void generateJBRFile(const QString& baseFileName,
                         const QVector<QVector<double>>& allPoints,
                         int totalPoints);

signals:
    void signal_path(QString path);
};

#endif // TESTPOINTS_H
