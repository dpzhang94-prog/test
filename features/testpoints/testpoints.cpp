#include "testpoints.h"
#include "pcdmisclient.h"
#include "ui_testpoints.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSet>
#include <QSignalBlocker>
#include <QTemporaryFile>
#include <QTextStream>
#include <QVector>

#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <random>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#include <QVTKOpenGLNativeWidget.h>
#include <vtkActor.h>
#include <vtkAutoInit.h>
#include <vtkAxesActor.h>
#include <vtkCell.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkPointData.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkSelectEnclosedPoints.h>
#include <vtkSphereSource.h>
#include <vtkSTLReader.h>
#include <vtkUnsignedCharArray.h>

VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingOpenGL2);

namespace {

constexpr double kTrackerMinimumDistanceMm = 800.0;
constexpr double kTrackerMaximumDistanceMm = 160000.0;

// 创建测试点过滤所需的默认机器人机构参数。
HK_RobotParameters createDefaultKinematicsParameters()
{
    // 测试点STL过滤使用同一套机构参数，保证过滤计算和TCP/OCR校验一致。
    HK_RobotParameters params = {};
    params.L1 = 339.934;
    params.L2 = 177.553;
    params.L3 = 498.337;
    params.L4 = 500.0;
    params.L5 = 500.0;
    params.L6 = 51.337;
    params.L7 = 177.626;
    params.L8 = 391.747;
    params.L9 = 35.369;
    params.L10 = 195.249;
    params.L11 = 340.189;
    params.L12 = 177.509;
    params.L13 = 500.0;
    params.L14 = 0.36;
    params.L16 = -0.21;
    return params;
}

// 消除浮点计算产生的负零。
double normalizePointValue(double value)
{
    return std::abs(value) < 1e-9 ? 0.0 : value;
}

// 按当前精度设置生成整数或 0.5 步长的关节值。
double generatedPointValue(double value, bool allowDecimal)
{
    if (allowDecimal) {
        return normalizePointValue(std::round(value * 2.0) / 2.0);
    }

    return static_cast<int>(value);
}

// 将关节值格式化为输出文件使用的简洁文本。
QString formatPointValue(double value)
{
    value = normalizePointValue(value);
    if (std::abs(value - std::round(value)) < 1e-9) {
        return QString::number(static_cast<qint64>(std::llround(value)));
    }

    return QString::number(value, 'f', 1);
}

// 将关节值转换为测试点去重键。
QString pointKeyValue(double value)
{
    return QString::number(normalizePointValue(value), 'f', 1);
}

// 将运动学五轴姿态 R=Rx(rx)*Ry(ry) 转换为标准 ZYX 欧拉角
// R=Rz(z)*Ry(y)*Rx(x)，输出单位为度。
void fixedXyToZyxDegrees(
    double rx, double ry,
    double& zDegrees, double& yDegrees, double& xDegrees)
{
    const double sinX = std::sin(rx);
    const double cosX = std::cos(rx);
    const double sinY = std::sin(ry);
    const double cosY = std::cos(ry);

    const double r00 = cosY;
    const double r10 = sinX * sinY;
    const double r11 = cosX;
    const double r12 = -sinX * cosY;
    const double r20 = -cosX * sinY;
    const double r21 = sinX;
    const double r22 = cosY * cosX;

    const double y = std::asin(qBound(-1.0, -r20, 1.0));
    double x = 0.0;
    double z = 0.0;
    if (std::abs(std::cos(y)) > 1.0e-10) {
        x = std::atan2(r21, r22);
        z = std::atan2(r10, r00);
    } else {
        // RY=±90°时 RX/RZ 耦合，固定 RZ=0，保留等价的 RX。
        x = std::atan2(-r12, r11);
    }

    const double radiansToDegrees =
        180.0 / std::acos(-1.0);
    zDegrees = z * radiansToDegrees;
    yDegrees = y * radiansToDegrees;
    xDegrees = x * radiansToDegrees;
}

}

// 创建测试点窗口，初始化正解环境和STL区域选择视图。
TestPoints::TestPoints(PcdmisClient *pcdmisClient, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TestPoints)
    , m_stlPolyData(nullptr)
    , m_pcdmisClient(pcdmisClient)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("测试点生成"));

    // J6 是独立主轴，不参与 J1～J5 的测试位姿组合；输出文件中以 0° 作为整周起点。
    ui->lineEdit_J6_min->setText(QStringLiteral("0"));
    ui->lineEdit_J6_max->setText(QStringLiteral("0"));
    ui->lineEdit_J6_min->setReadOnly(true);
    ui->lineEdit_J6_max->setReadOnly(true);
    const QString j6Hint = QStringLiteral(
        "J6为独立主轴，不参与五轴正解和测试点组合；"
        "可见性筛选会从0°开始模拟完整一周。");
    ui->lineEdit_J6_min->setToolTip(j6Hint);
    ui->lineEdit_J6_max->setToolTip(j6Hint);

    initializeKinematicsContext();
    initializeStlView();

    // 未加载 STL 时明确关闭过滤，生成测试点不依赖模型。
    ui->checkBox_filter->setChecked(false);

    // 禁止 QDialog 将回车键自动映射到按钮，避免在输入框回车时打开 STL 选择框。
    const QList<QPushButton*> buttons = {
        ui->loadStlButton,
        ui->resetViewButton,
        ui->resetRegionButton,
        ui->refreshTrackerButton,
        ui->testTrackerPositionButton,
        ui->previewTrackerButton,
        ui->exportPreviewPoseButton,
        ui->pushButton_Confirm
    };
    for (QPushButton* button : buttons) {
        button->setAutoDefault(false);
        button->setDefault(false);
    }

    connect(ui->loadStlButton, &QPushButton::clicked,
            this, &TestPoints::chooseStlModel);
    connect(ui->resetViewButton, &QPushButton::clicked,
            this, &TestPoints::resetCamera);
    connect(ui->resetRegionButton, &QPushButton::clicked,
            this, &TestPoints::resetRegion);
    connect(ui->checkBox_Decimal, &QCheckBox::toggled, this, [this]() {
        on_lineEdit_count_editingFinished();
    });
    connect(ui->regionSizeSlider, &QSlider::valueChanged,
            this, &TestPoints::updateRegion);
    connect(ui->regionXSlider, &QSlider::valueChanged,
            this, &TestPoints::updateRegion);
    connect(ui->regionYSlider, &QSlider::valueChanged,
            this, &TestPoints::updateRegion);
    connect(ui->regionZSlider, &QSlider::valueChanged,
            this, &TestPoints::updateRegion);
    connect(ui->refreshTrackerButton, &QPushButton::clicked,
            this, &TestPoints::refreshTrackerPosition);
    connect(ui->testTrackerPositionButton, &QPushButton::clicked,
            this, &TestPoints::useTestTrackerPosition);
    connect(ui->previewTrackerButton, &QPushButton::clicked,
            this, &TestPoints::previewTrackerVisibility);
    connect(ui->exportPreviewPoseButton, &QPushButton::clicked,
            this, &TestPoints::exportPreviewRetainedPoses);
    connect(ui->trackerVisibilityCheckBox, &QCheckBox::toggled,
            this, &TestPoints::updateTrackerUiState);
    connect(ui->showTrackerRangeCheckBox, &QCheckBox::toggled,
            this, &TestPoints::updateTrackerVisualization);

    const auto invalidatePreview = [this]() {
        m_previewRetainedJointPoints.clear();
        ui->exportPreviewPoseButton->setEnabled(false);
        updateVisibilityPreview({});
        ui->trackerResultLabel->setText(
            QStringLiteral(
                "最终筛选：参数已更改，请点击“预览筛选”重新计算\n"
                "关节范围生成：--　去重：--　"
                "扩散区域过滤：--　J6整周过滤：--"));
    };
    connect(ui->reflectorAxisComboBox, &QComboBox::currentIndexChanged,
            this, invalidatePreview);
    connect(ui->reflectorOffsetXSpinBox, &QDoubleSpinBox::valueChanged,
            this, invalidatePreview);
    connect(ui->reflectorOffsetYSpinBox, &QDoubleSpinBox::valueChanged,
            this, invalidatePreview);
    connect(ui->reflectorOffsetZSpinBox, &QDoubleSpinBox::valueChanged,
            this, invalidatePreview);
    connect(ui->incidenceAngleSpinBox, &QDoubleSpinBox::valueChanged,
            this, invalidatePreview);
    connect(ui->rotationStepSpinBox, &QSpinBox::valueChanged,
            this, invalidatePreview);
    connect(ui->checkBox_Decimal, &QCheckBox::toggled,
            this, invalidatePreview);
    connect(ui->checkBox_filter, &QCheckBox::toggled,
            this, invalidatePreview);
    connect(ui->trackerVisibilityCheckBox, &QCheckBox::toggled,
            this, invalidatePreview);
    connect(ui->regionSizeSlider, &QSlider::valueChanged,
            this, invalidatePreview);
    connect(ui->regionXSlider, &QSlider::valueChanged,
            this, invalidatePreview);
    connect(ui->regionYSlider, &QSlider::valueChanged,
            this, invalidatePreview);
    connect(ui->regionZSlider, &QSlider::valueChanged,
            this, invalidatePreview);

    const QList<QLineEdit*> previewInputEdits = {
        ui->lineEdit_J1_min, ui->lineEdit_J1_max,
        ui->lineEdit_J2_min, ui->lineEdit_J2_max,
        ui->lineEdit_J3_min, ui->lineEdit_J3_max,
        ui->lineEdit_J4_min, ui->lineEdit_J4_max,
        ui->lineEdit_J5_min, ui->lineEdit_J5_max,
        ui->lineEdit_count
    };
    for (QLineEdit* edit : previewInputEdits) {
        connect(edit, &QLineEdit::textChanged,
                this, invalidatePreview);
    }

    if (m_pcdmisClient != nullptr) {
        connect(m_pcdmisClient, &PcdmisClient::connectedChanged,
                this, [this](bool) { updateTrackerUiState(); });
        connect(m_pcdmisClient, &PcdmisClient::trackerOriginChanged,
                this, [this](double x, double y, double z) {
                    // 坐标由工作线程通过信号送达，直接使用信号参数，
                    // 不跨线程访问任何 COM 或 Worker 状态。
                    m_trackerOrigin[0] = x;
                    m_trackerOrigin[1] = y;
                    m_trackerOrigin[2] = z;
                    m_trackerOriginValid = true;
                    m_trackerOriginIsSimulated = false;
                    m_previewRetainedJointPoints.clear();
                    ui->exportPreviewPoseButton->setEnabled(false);
                    updateVisibilityPreview({});
                    ui->trackerResultLabel->setText(
                        QStringLiteral(
                            "最终筛选：仪器位置已变化，请重新预览\n"
                            "关节范围生成：--　去重：--　"
                            "扩散区域过滤：--　J6整周过滤：--"));
                    updateTrackerUiState();
                    updateTrackerVisualization();
                });
        connect(m_pcdmisClient,
                &PcdmisClient::trackerOriginRefreshFinished,
                this,
                &TestPoints::handleTrackerOriginRefreshFinished);

        if (m_pcdmisClient->hasAlignedTrackerOrigin()) {
            const auto origin = m_pcdmisClient->alignedTrackerOrigin();
            m_trackerOrigin[0] = origin[0];
            m_trackerOrigin[1] = origin[1];
            m_trackerOrigin[2] = origin[2];
            m_trackerOriginValid = true;
        }
    }
    updateTrackerUiState();
    updateTrackerVisualization();
}

// 释放正解上下文和窗口资源。
TestPoints::~TestPoints()
{
    if (m_kinematicsContext)
    {
        HK_DestroyContext(m_kinematicsContext);
        m_kinematicsContext = nullptr;
    }
    delete ui;
}

// 初始化 VTK 渲染窗口、扩散中心标记和 STL 自身坐标系。
void TestPoints::initializeStlView()
{
    ui->stlView->setFormat(QVTKOpenGLNativeWidget::defaultFormat());

    const auto renderWindow =
        vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_renderer->SetBackground(0.10, 0.12, 0.16);
    renderWindow->AddRenderer(m_renderer);
    ui->stlView->setRenderWindow(renderWindow);

    m_centerSource = vtkSmartPointer<vtkSphereSource>::New();
    m_centerSource->SetThetaResolution(24);
    m_centerSource->SetPhiResolution(16);
    const auto centerMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    centerMapper->SetInputConnection(m_centerSource->GetOutputPort());

    m_centerActor = vtkSmartPointer<vtkActor>::New();
    m_centerActor->SetMapper(centerMapper);
    m_centerActor->GetProperty()->SetColor(0.20, 1.0, 0.35);
    m_centerActor->SetVisibility(false);
    m_renderer->AddActor(m_centerActor);

    m_axesActor = vtkSmartPointer<vtkAxesActor>::New();
    m_axesActor->SetPosition(0.0, 0.0, 0.0);
    m_axesActor->SetShaftTypeToCylinder();
    m_axesActor->SetTipTypeToCone();
    m_axesActor->AxisLabelsOn();
    m_axesActor->SetVisibility(false);
    m_renderer->AddActor(m_axesActor);

    m_trackerSource = vtkSmartPointer<vtkSphereSource>::New();
    m_trackerSource->SetThetaResolution(28);
    m_trackerSource->SetPhiResolution(20);
    const auto trackerMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    trackerMapper->SetInputConnection(m_trackerSource->GetOutputPort());
    m_trackerActor = vtkSmartPointer<vtkActor>::New();
    m_trackerActor->SetMapper(trackerMapper);
    m_trackerActor->GetProperty()->SetColor(1.0, 0.55, 0.12);
    m_trackerActor->GetProperty()->SetAmbient(0.35);
    m_trackerActor->SetVisibility(false);
    m_renderer->AddActor(m_trackerActor);

    m_trackerRangeSource = vtkSmartPointer<vtkSphereSource>::New();
    m_trackerRangeSource->SetThetaResolution(48);
    m_trackerRangeSource->SetPhiResolution(32);
    const auto trackerRangeMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    trackerRangeMapper->SetInputConnection(
        m_trackerRangeSource->GetOutputPort());
    m_trackerRangeActor = vtkSmartPointer<vtkActor>::New();
    m_trackerRangeActor->SetMapper(trackerRangeMapper);
    m_trackerRangeActor->GetProperty()->SetColor(0.20, 0.72, 1.0);
    m_trackerRangeActor->GetProperty()->SetOpacity(0.12);
    m_trackerRangeActor->GetProperty()->SetRepresentationToWireframe();
    m_trackerRangeActor->GetProperty()->SetLineWidth(1.2);
    m_trackerRangeActor->UseBoundsOff();
    m_trackerRangeActor->SetVisibility(false);
    m_renderer->AddActor(m_trackerRangeActor);

    m_trackerInnerRangeSource = vtkSmartPointer<vtkSphereSource>::New();
    m_trackerInnerRangeSource->SetThetaResolution(36);
    m_trackerInnerRangeSource->SetPhiResolution(24);
    const auto trackerInnerRangeMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    trackerInnerRangeMapper->SetInputConnection(
        m_trackerInnerRangeSource->GetOutputPort());
    m_trackerInnerRangeActor = vtkSmartPointer<vtkActor>::New();
    m_trackerInnerRangeActor->SetMapper(trackerInnerRangeMapper);
    m_trackerInnerRangeActor->GetProperty()->SetColor(1.0, 0.28, 0.22);
    m_trackerInnerRangeActor->GetProperty()->SetOpacity(0.16);
    m_trackerInnerRangeActor->GetProperty()->SetRepresentationToWireframe();
    m_trackerInnerRangeActor->UseBoundsOff();
    m_trackerInnerRangeActor->SetVisibility(false);
    m_renderer->AddActor(m_trackerInnerRangeActor);

    m_visibilityPointsPolyData = vtkSmartPointer<vtkPolyData>::New();
    const auto visibilityMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    visibilityMapper->SetInputData(m_visibilityPointsPolyData);
    visibilityMapper->SetScalarModeToUsePointData();
    visibilityMapper->SetColorModeToDirectScalars();
    visibilityMapper->ScalarVisibilityOn();
    m_visibilityPointsActor = vtkSmartPointer<vtkActor>::New();
    m_visibilityPointsActor->SetMapper(visibilityMapper);
    m_visibilityPointsActor->GetProperty()->SetPointSize(7.0);
    m_visibilityPointsActor->GetProperty()->SetRenderPointsAsSpheres(true);
    m_visibilityPointsActor->SetVisibility(false);
    m_renderer->AddActor(m_visibilityPointsActor);
}

// 选择一个STL文件并将其载入三维视图。
void TestPoints::chooseStlModel()
{
    const QString filePath = QFileDialog::getOpenFileName(
        this, QStringLiteral("选择可达区域 STL 模型"), QString(),
        QStringLiteral("STL 文件 (*.stl);;所有文件 (*.*)"));
    if (filePath.isEmpty()) {
        return;
    }

    if (!loadSTLModel(filePath)) {
        QMessageBox::warning(this, QStringLiteral("加载失败"),
                             QStringLiteral("STL 模型无有效三角面，无法加载。"));
    }
}

// 将扩散中心恢复为自动计算的位置，并把扩散范围恢复为 40%。
void TestPoints::resetRegion()
{
    if (m_stlPolyData == nullptr) {
        return;
    }

    const QSignalBlocker sizeBlocker(ui->regionSizeSlider);
    const QSignalBlocker xBlocker(ui->regionXSlider);
    const QSignalBlocker yBlocker(ui->regionYSlider);
    const QSignalBlocker zBlocker(ui->regionZSlider);

    ui->regionSizeSlider->setValue(40);
    QSlider* sliders[3] = {
        ui->regionXSlider, ui->regionYSlider, ui->regionZSlider
    };
    for (int axis = 0; axis < 3; ++axis) {
        const double span =
            m_stlBounds[axis * 2 + 1] - m_stlBounds[axis * 2];
        const double ratio = span > 0.0
            ? (m_defaultRegionCenter[axis] - m_stlBounds[axis * 2])
                / span
            : 0.5;
        const int sliderRange =
            sliders[axis]->maximum() - sliders[axis]->minimum();
        sliders[axis]->setValue(
            sliders[axis]->minimum()
            + qBound(0, qRound(ratio * sliderRange), sliderRange));
    }
    updateRegion();
}

// 将相机调整到能够完整观察当前STL模型的位置。
void TestPoints::resetCamera()
{
    if (m_stlPolyData == nullptr && !m_trackerOriginValid) {
        return;
    }

    m_renderer->ResetCamera();
    m_renderer->ResetCameraClippingRange();
    ui->stlView->renderWindow()->Render();
}

// 从主窗口共享的 PC-DMIS 客户端刷新跟踪仪在活动对齐中的原点。
void TestPoints::refreshTrackerPosition()
{
    if (m_pcdmisClient == nullptr || !m_pcdmisClient->isConnected()) {
        m_trackerOriginValid = false;
        updateTrackerUiState();
        updateTrackerVisualization();
        QMessageBox::information(
            this, QStringLiteral("尚未连接"),
            QStringLiteral("请先在主界面连接 PC-DMIS，再获取仪器位置。"));
        return;
    }

    if (m_trackerRefreshPending) {
        return;
    }

    m_trackerRefreshPending = true;
    ui->trackerStatusLabel->setText(QStringLiteral("正在从 PC-DMIS 获取仪器位置..."));
    updateTrackerUiState();
    m_pcdmisClient->refreshAlignedTrackerOrigin();
}

void TestPoints::handleTrackerOriginRefreshFinished(
    bool success, double x, double y, double z,
    const QString &errorMessage)
{
    if (!m_trackerRefreshPending) {
        return;
    }
    m_trackerRefreshPending = false;

    if (!success) {
        m_trackerOriginValid = false;
        updateTrackerUiState();
        updateTrackerVisualization();
        QMessageBox::information(
            this, QStringLiteral("没有取得仪器位置"),
            errorMessage.isEmpty()
                ? QStringLiteral(
                      "请确认 PC-DMIS 中已经建立并激活与机器人基坐标一致的对齐坐标系。")
                : errorMessage);
        return;
    }

    m_trackerOrigin[0] = x;
    m_trackerOrigin[1] = y;
    m_trackerOrigin[2] = z;
    m_trackerOriginValid = true;
    m_trackerOriginIsSimulated = false;
    m_previewRetainedJointPoints.clear();
    ui->exportPreviewPoseButton->setEnabled(false);
    ui->trackerResultLabel->setText(
        QStringLiteral(
            "最终筛选：仪器位置已刷新，请点击“预览筛选”重新计算\n"
            "关节范围生成：--　去重：--　"
            "扩散区域过滤：--　J6整周过滤：--"));
    updateVisibilityPreview({});
    updateTrackerUiState();
    updateTrackerVisualization();
    resetCamera();
}

// 使用固定的模拟跟踪仪位置，不让 STL 加载状态影响测试坐标。
void TestPoints::useTestTrackerPosition()
{
    // 机器人基坐标系中的固定测试值，单位 mm。
    m_trackerOrigin[0] = 0.0;
    m_trackerOrigin[1] = -4000.0;
    m_trackerOrigin[2] = -4000.0;

    m_trackerOriginValid = true;
    m_trackerOriginIsSimulated = true;
    m_previewRetainedJointPoints.clear();
    ui->exportPreviewPoseButton->setEnabled(false);
    ui->trackerResultLabel->setText(
        QStringLiteral(
            "最终筛选：已使用模拟仪器位置，请点击“预览筛选”计算\n"
            "关节范围生成：--　去重：--　"
            "扩散区域过滤：--　J6整周过滤：--"));
    updateVisibilityPreview({});
    updateTrackerUiState();
    updateTrackerVisualization();
    resetCamera();
}

// 根据连接和原点有效状态更新筛选控件及文字提示。
void TestPoints::updateTrackerUiState()
{
    const bool connected =
        m_pcdmisClient != nullptr && m_pcdmisClient->isConnected();
    ui->refreshTrackerButton->setEnabled(
        connected && !m_trackerRefreshPending);
    ui->testTrackerPositionButton->setEnabled(!m_trackerRefreshPending);
    // 预览按钮还可用于只执行关节范围或 STL 区域过滤，不依赖仪器连接。
    ui->previewTrackerButton->setEnabled(true);

    if (m_trackerRefreshPending) {
        ui->trackerStatusLabel->setText(
            QStringLiteral("正在从 PC-DMIS 获取仪器位置..."));
        ui->trackerStatusLabel->setStyleSheet(
            QStringLiteral("color: #0b57d0; font-weight: 600;"));
        return;
    }

    if (m_trackerOriginValid && m_trackerOriginIsSimulated) {
        ui->trackerStatusLabel->setText(
            QStringLiteral("模拟位置（不来自 PC-DMIS）"));
        ui->trackerStatusLabel->setStyleSheet(
            QStringLiteral("color: #0b57d0; font-weight: 600;"));
        ui->trackerPositionLabel->setText(
            QStringLiteral("测试位置：X %1   Y %2   Z %3 mm")
                .arg(m_trackerOrigin[0], 0, 'f', 3)
                .arg(m_trackerOrigin[1], 0, 'f', 3)
                .arg(m_trackerOrigin[2], 0, 'f', 3));
    } else if (m_trackerOriginValid) {
        ui->trackerStatusLabel->setText(
            QStringLiteral("位置有效（当前 PC-DMIS 活动对齐）"));
        ui->trackerStatusLabel->setStyleSheet(
            QStringLiteral("color: #137333; font-weight: 600;"));
        ui->trackerPositionLabel->setText(
            QStringLiteral("位置：X %1   Y %2   Z %3 mm")
                .arg(m_trackerOrigin[0], 0, 'f', 3)
                .arg(m_trackerOrigin[1], 0, 'f', 3)
                .arg(m_trackerOrigin[2], 0, 'f', 3));
    } else if (connected) {
        ui->trackerStatusLabel->setText(
            QStringLiteral("已连接，请获取活动对齐中的仪器位置"));
        ui->trackerStatusLabel->setStyleSheet(
            QStringLiteral("color: #9a6700; font-weight: 600;"));
        ui->trackerPositionLabel->setText(
            QStringLiteral("位置：X --   Y --   Z --"));
    } else {
        ui->trackerStatusLabel->setText(
            QStringLiteral("PC-DMIS 未连接"));
        ui->trackerStatusLabel->setStyleSheet(
            QStringLiteral("color: #b3261e; font-weight: 600;"));
        ui->trackerPositionLabel->setText(
            QStringLiteral("位置：X --   Y --   Z --"));
    }
}

// 在 STL 视图中显示跟踪仪原点、近场排除区及覆盖当前模型的范围球。
void TestPoints::updateTrackerVisualization()
{
    if (m_renderer == nullptr || m_trackerSource == nullptr) {
        return;
    }

    const bool showRange =
        m_trackerOriginValid && ui->showTrackerRangeCheckBox->isChecked();
    m_trackerActor->SetVisibility(m_trackerOriginValid);
    m_trackerRangeActor->SetVisibility(showRange);
    m_trackerInnerRangeActor->SetVisibility(showRange);

    if (m_trackerOriginValid) {
        double modelScale = 1000.0;
        double displayRange = 2000.0;
        if (m_stlPolyData != nullptr) {
            const double xLength = m_stlBounds[1] - m_stlBounds[0];
            const double yLength = m_stlBounds[3] - m_stlBounds[2];
            const double zLength = m_stlBounds[5] - m_stlBounds[4];
            modelScale = qMax(1.0, qMax(xLength, qMax(yLength, zLength)));

            double maximumCornerDistance = 0.0;
            for (int xIndex = 0; xIndex < 2; ++xIndex) {
                for (int yIndex = 0; yIndex < 2; ++yIndex) {
                    for (int zIndex = 0; zIndex < 2; ++zIndex) {
                        const double dx =
                            m_stlBounds[xIndex] - m_trackerOrigin[0];
                        const double dy =
                            m_stlBounds[2 + yIndex] - m_trackerOrigin[1];
                        const double dz =
                            m_stlBounds[4 + zIndex] - m_trackerOrigin[2];
                        maximumCornerDistance = qMax(
                            maximumCornerDistance,
                            std::sqrt(dx * dx + dy * dy + dz * dz));
                    }
                }
            }
            displayRange = qBound(
                kTrackerMinimumDistanceMm,
                maximumCornerDistance * 1.03,
                kTrackerMaximumDistanceMm);
        }

        const double trackerRadius = qMax(12.0, modelScale * 0.018);
        m_trackerSource->SetCenter(m_trackerOrigin);
        m_trackerSource->SetRadius(trackerRadius);
        m_trackerSource->Update();

        m_trackerRangeSource->SetCenter(m_trackerOrigin);
        m_trackerRangeSource->SetRadius(displayRange);
        m_trackerRangeSource->Update();

        m_trackerInnerRangeSource->SetCenter(m_trackerOrigin);
        m_trackerInnerRangeSource->SetRadius(kTrackerMinimumDistanceMm);
        m_trackerInnerRangeSource->Update();
    }

    ui->stlView->renderWindow()->Render();
}

// 仅用绿色点显示完整筛选流水线最终保留的 TCP。
void TestPoints::updateVisibilityPreview(
    const QVector<Point3D>& retainedPositions)
{
    const auto points = vtkSmartPointer<vtkPoints>::New();
    const auto vertices = vtkSmartPointer<vtkCellArray>::New();
    const auto colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetName("VisibilityColors");
    colors->SetNumberOfComponents(3);

    const unsigned char retainedColor[3] = {46, 214, 102};
    for (const Point3D& position : retainedPositions) {
        const vtkIdType pointId = points->InsertNextPoint(
            position.x, position.y, position.z);
        vertices->InsertNextCell(1, &pointId);
        colors->InsertNextTypedTuple(retainedColor);
    }

    m_visibilityPointsPolyData->SetPoints(points);
    m_visibilityPointsPolyData->SetVerts(vertices);
    m_visibilityPointsPolyData->GetPointData()->SetScalars(colors);
    m_visibilityPointsPolyData->Modified();
    m_visibilityPointsActor->SetVisibility(!retainedPositions.isEmpty());
    ui->stlView->renderWindow()->Render();
}

// 根据扩散范围和中心滑动条更新模型三角面颜色及中心状态。
void TestPoints::updateRegion()
{
    if (m_stlPolyData == nullptr) {
        return;
    }

    const int positions[3] = {
        ui->regionXSlider->value(),
        ui->regionYSlider->value(),
        ui->regionZSlider->value()
    };
    QSlider* sliders[3] = {
        ui->regionXSlider, ui->regionYSlider, ui->regionZSlider
    };
    for (int axis = 0; axis < 3; ++axis) {
        const double modelMin = m_stlBounds[axis * 2];
        const double modelMax = m_stlBounds[axis * 2 + 1];
        const double sliderRange =
            sliders[axis]->maximum() - sliders[axis]->minimum();
        const double ratio = sliderRange > 0.0
            ? (positions[axis] - sliders[axis]->minimum()) / sliderRange
            : 0.5;
        m_regionCenter[axis] = modelMin +
            (modelMax - modelMin) * ratio;
    }

    const Point3D center = {
        m_regionCenter[0], m_regionCenter[1], m_regionCenter[2]
    };
    m_regionCenterValid = isPointInsideSTL(center);

    QVector<double> cellDistances;
    cellDistances.reserve(m_stlPolyData->GetNumberOfCells());
    double minDistance = std::numeric_limits<double>::max();
    for (vtkIdType cellIndex = 0;
         cellIndex < m_stlPolyData->GetNumberOfCells();
         ++cellIndex) {
        vtkCell* cell = m_stlPolyData->GetCell(cellIndex);
        Point3D cellCenter{0.0, 0.0, 0.0};
        const vtkIdType pointCount = cell->GetNumberOfPoints();
        for (vtkIdType pointIndex = 0;
             pointIndex < pointCount;
             ++pointIndex) {
            double point[3] = {};
            m_stlPolyData->GetPoint(
                cell->GetPointId(pointIndex), point);
            cellCenter.x += point[0];
            cellCenter.y += point[1];
            cellCenter.z += point[2];
        }
        if (pointCount > 0) {
            cellCenter.x /= pointCount;
            cellCenter.y /= pointCount;
            cellCenter.z /= pointCount;
        }

        const double distance = normalizedRegionDistance(cellCenter);
        cellDistances.append(distance);
        minDistance = qMin(minDistance, distance);
    }

    double maxDistance = minDistance;
    for (vtkIdType pointIndex = 0;
         pointIndex < m_stlPolyData->GetNumberOfPoints();
         ++pointIndex) {
        double point[3] = {};
        m_stlPolyData->GetPoint(pointIndex, point);
        maxDistance = qMax(
            maxDistance,
            normalizedRegionDistance({point[0], point[1], point[2]}));
    }

    const double progress = ui->regionSizeSlider->value() / 100.0;
    m_regionThreshold =
        minDistance + (maxDistance - minDistance) * progress;

    const unsigned char selectedColor[3] = {46, 204, 92};
    const unsigned char normalColor[3] = {174, 180, 190};
    for (vtkIdType cellIndex = 0;
         cellIndex < cellDistances.size();
         ++cellIndex) {
        m_modelCellColors->SetTypedTuple(
            cellIndex,
            cellDistances[cellIndex] <= m_regionThreshold
                ? selectedColor
                : normalColor);
    }
    m_modelCellColors->Modified();
    m_stlPolyData->Modified();

    m_centerSource->SetCenter(m_regionCenter);
    m_centerSource->Update();
    m_centerActor->GetProperty()->SetColor(
        m_regionCenterValid ? 0.20 : 1.0,
        m_regionCenterValid ? 1.0 : 0.20,
        0.20);
    m_centerActor->SetVisibility(true);

    ui->regionSizeValueLabel->setText(
        QStringLiteral("%1%").arg(ui->regionSizeSlider->value()));
    ui->regionXValueLabel->setText(
        QString::number(m_regionCenter[0], 'f', 1));
    ui->regionYValueLabel->setText(
        QString::number(m_regionCenter[1], 'f', 1));
    ui->regionZValueLabel->setText(
        QString::number(m_regionCenter[2], 'f', 1));
    ui->regionBoundsLabel->setText(
        m_regionCenterValid
            ? QStringLiteral("中心有效，绿色表面为当前扩散范围")
            : QStringLiteral("中心位于 STL 外部，请调整 X/Y/Z"));

    ui->stlView->renderWindow()->Render();
}

// 计算闭合 STL 的体积质心，并在必要时寻找靠近包围盒中心的内部点。
TestPoints::Point3D TestPoints::calculateDefaultRegionCenter()
{
    Point3D boundsCenter{
        (m_stlBounds[0] + m_stlBounds[1]) * 0.5,
        (m_stlBounds[2] + m_stlBounds[3]) * 0.5,
        (m_stlBounds[4] + m_stlBounds[5]) * 0.5
    };

    double totalVolume = 0.0;
    double weightedCenter[3] = {};
    for (vtkIdType cellIndex = 0;
         cellIndex < m_stlPolyData->GetNumberOfCells();
         ++cellIndex) {
        vtkCell* cell = m_stlPolyData->GetCell(cellIndex);
        if (cell->GetNumberOfPoints() != 3) {
            continue;
        }

        double p0[3] = {};
        double p1[3] = {};
        double p2[3] = {};
        m_stlPolyData->GetPoint(cell->GetPointId(0), p0);
        m_stlPolyData->GetPoint(cell->GetPointId(1), p1);
        m_stlPolyData->GetPoint(cell->GetPointId(2), p2);

        const double cross[3] = {
            p1[1] * p2[2] - p1[2] * p2[1],
            p1[2] * p2[0] - p1[0] * p2[2],
            p1[0] * p2[1] - p1[1] * p2[0]
        };
        const double volume =
            (p0[0] * cross[0] + p0[1] * cross[1]
             + p0[2] * cross[2]) / 6.0;
        totalVolume += volume;
        for (int axis = 0; axis < 3; ++axis) {
            weightedCenter[axis] +=
                volume * (p0[axis] + p1[axis] + p2[axis]) * 0.25;
        }
    }

    if (std::abs(totalVolume) > 1e-9) {
        const Point3D volumeCenter{
            weightedCenter[0] / totalVolume,
            weightedCenter[1] / totalVolume,
            weightedCenter[2] / totalVolume
        };
        if (isPointInsideSTL(volumeCenter)) {
            return volumeCenter;
        }
    }

    if (isPointInsideSTL(boundsCenter)) {
        return boundsCenter;
    }

    Point3D bestPoint = boundsCenter;
    double bestDistance = std::numeric_limits<double>::max();
    constexpr int sampleCount = 9;
    for (int ix = 1; ix <= sampleCount; ++ix) {
        for (int iy = 1; iy <= sampleCount; ++iy) {
            for (int iz = 1; iz <= sampleCount; ++iz) {
                const Point3D candidate{
                    m_stlBounds[0] +
                        (m_stlBounds[1] - m_stlBounds[0])
                            * ix / (sampleCount + 1.0),
                    m_stlBounds[2] +
                        (m_stlBounds[3] - m_stlBounds[2])
                            * iy / (sampleCount + 1.0),
                    m_stlBounds[4] +
                        (m_stlBounds[5] - m_stlBounds[4])
                            * iz / (sampleCount + 1.0)
                };
                if (!isPointInsideSTL(candidate)) {
                    continue;
                }

                const double dx =
                    (candidate.x - boundsCenter.x)
                    / m_regionHalfLengths[0];
                const double dy =
                    (candidate.y - boundsCenter.y)
                    / m_regionHalfLengths[1];
                const double dz =
                    (candidate.z - boundsCenter.z)
                    / m_regionHalfLengths[2];
                const double distance =
                    dx * dx + dy * dy + dz * dz;
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestPoint = candidate;
                }
            }
        }
    }

    return bestPoint;
}

// 计算点到扩散中心的归一化椭球距离。
double TestPoints::normalizedRegionDistance(const Point3D& point) const
{
    const double dx =
        (point.x - m_regionCenter[0]) / m_regionHalfLengths[0];
    const double dy =
        (point.y - m_regionCenter[1]) / m_regionHalfLengths[1];
    const double dz =
        (point.z - m_regionCenter[2]) / m_regionHalfLengths[2];
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// 根据当前输入估算去重后的测试点数量。
void TestPoints::on_lineEdit_count_editingFinished()
{
    bool ok;
    int count = ui->lineEdit_count->text().toInt(&ok);
    if (!ok || count <= 0) {
        ui->label_expected_count->clear();
        return;
    }

    double j_min[6], j_max[6];
    QLineEdit* minEdits[6] = {ui->lineEdit_J1_min, ui->lineEdit_J2_min, ui->lineEdit_J3_min,
                              ui->lineEdit_J4_min, ui->lineEdit_J5_min, ui->lineEdit_J6_min};
    QLineEdit* maxEdits[6] = {ui->lineEdit_J1_max, ui->lineEdit_J2_max, ui->lineEdit_J3_max,
                              ui->lineEdit_J4_max, ui->lineEdit_J5_max, ui->lineEdit_J6_max};

    QVector<int> validJoints;
    for (int i = 0; i < 6; i++) {
        j_min[i] = minEdits[i]->text().toDouble(&ok);
        if (!ok) {
            ui->label_expected_count->clear();
            return;
        }

        j_max[i] = maxEdits[i]->text().toDouble(&ok);
        if (!ok) {
            ui->label_expected_count->clear();
            return;
        }

        if (i < 5 && j_max[i] > j_min[i]) {
            validJoints.append(i);
        }
    }

    int n = validJoints.size();
    // 只要存在有效关节，就允许生成测试点
    if (n <= 0) {
        ui->label_expected_count->clear();
        return;
    }

    const bool allowDecimal = ui->checkBox_Decimal->isChecked();
    QVector<QVector<double>> allPoints =
        generateAllTestPoints(
            j_min, j_max, validJoints, count, allowDecimal);
    QVector<QVector<double>> uniquePoints = removeDuplicatePoints(allPoints);

    ui->label_expected_count->setText(QString::number(uniquePoints.size()));
}

// 使用当前输入生成一次候选点，供预览和最终保存共同使用。
bool TestPoints::generateCandidatePointsFromUi(
    QVector<QVector<double>>& uniquePoints,
    int& generatedCount, QString& errorMessage)
{
    uniquePoints.clear();
    generatedCount = 0;
    errorMessage.clear();

    bool ok = false;
    const int count = ui->lineEdit_count->text().toInt(&ok);
    if (!ok || count <= 0) {
        errorMessage = QStringLiteral("请输入有效的点数量！");
        return false;
    }

    double jointMinimum[6] = {};
    double jointMaximum[6] = {};
    QLineEdit* minimumEdits[6] = {
        ui->lineEdit_J1_min, ui->lineEdit_J2_min,
        ui->lineEdit_J3_min, ui->lineEdit_J4_min,
        ui->lineEdit_J5_min, ui->lineEdit_J6_min
    };
    QLineEdit* maximumEdits[6] = {
        ui->lineEdit_J1_max, ui->lineEdit_J2_max,
        ui->lineEdit_J3_max, ui->lineEdit_J4_max,
        ui->lineEdit_J5_max, ui->lineEdit_J6_max
    };

    QVector<int> validJoints;
    for (int jointIndex = 0; jointIndex < 6; ++jointIndex) {
        jointMinimum[jointIndex] =
            minimumEdits[jointIndex]->text().toDouble(&ok);
        if (!ok) {
            errorMessage = QStringLiteral("J%1 最小值无效！")
                               .arg(jointIndex + 1);
            return false;
        }

        jointMaximum[jointIndex] =
            maximumEdits[jointIndex]->text().toDouble(&ok);
        if (!ok) {
            errorMessage = QStringLiteral("J%1 最大值无效！")
                               .arg(jointIndex + 1);
            return false;
        }

        if (jointIndex < 5 &&
            jointMaximum[jointIndex] > jointMinimum[jointIndex]) {
            validJoints.append(jointIndex);
        }
    }

    if (validJoints.isEmpty()) {
        errorMessage =
            QStringLiteral("至少需要一个关节的最大值大于最小值！");
        return false;
    }

    const bool allowDecimal = ui->checkBox_Decimal->isChecked();
    const QVector<QVector<double>> generatedPoints =
        generateAllTestPoints(
            jointMinimum, jointMaximum, validJoints, count,
            allowDecimal);
    generatedCount = generatedPoints.size();
    uniquePoints = removeDuplicatePoints(generatedPoints);
    if (uniquePoints.size() < count) {
        errorMessage = QStringLiteral(
            "当前关节范围和精度无法生成 %1 个唯一点，"
            "仅生成了 %2 个。请扩大关节范围或调整精度。")
                           .arg(count)
                           .arg(uniquePoints.size());
        return false;
    }
    return true;
}

// 按当前复选框顺序执行完整筛选，只显示并缓存最终保留点。
void TestPoints::previewTrackerVisibility()
{
    m_previewRetainedJointPoints.clear();
    ui->exportPreviewPoseButton->setEnabled(false);

    const bool useRegionFilter = ui->checkBox_filter->isChecked();
    const bool useTrackerFilter =
        ui->trackerVisibilityCheckBox->isChecked();

    if (useRegionFilter && m_stlPolyData == nullptr) {
        QMessageBox::warning(
            this, QStringLiteral("无法执行扩散区域过滤"),
            QStringLiteral(
                "已经勾选“使用当前扩散区域过滤”，但尚未加载 STL 模型。"));
        return;
    }
    if (useRegionFilter && !m_regionCenterValid) {
        QMessageBox::warning(
            this, QStringLiteral("扩散中心无效"),
            QStringLiteral(
                "当前扩散中心位于 STL 模型外部，请调整 X/Y/Z，"
                "或点击“恢复默认中心”。"));
        return;
    }
    if (useTrackerFilter && !m_trackerOriginValid) {
        QMessageBox::warning(
            this, QStringLiteral("缺少仪器位置"),
            QStringLiteral(
                "已经勾选“生成时启用 J6 整周可见性筛选”，"
                "请先获取仪器位置或使用测试位置。"));
        return;
    }
    if (useTrackerFilter) {
        QString installationError;
        if (!validateReflectorInstallation(installationError)) {
            QMessageBox::warning(
                this, QStringLiteral("靶球安装参数无效"),
                installationError);
            return;
        }
    }

    QVector<QVector<double>> candidatePoints;
    int generatedCount = 0;
    QString errorMessage;
    if (!generateCandidatePointsFromUi(
            candidatePoints, generatedCount, errorMessage)) {
        QMessageBox::warning(
            this, QStringLiteral("无法预览"), errorMessage);
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    int regionFilteredCount = 0;
    const QVector<QVector<double>> regionRetainedPoints =
        useRegionFilter
            ? filterUnreachablePoints(
                  candidatePoints, regionFilteredCount)
            : candidatePoints;

    int trackerFilteredCount = 0;
    const QVector<QVector<double>> finalPoints =
        useTrackerFilter
            ? filterTrackerVisiblePoints(
                  regionRetainedPoints, trackerFilteredCount)
            : regionRetainedPoints;

    QVector<Point3D> retainedPositions;
    retainedPositions.reserve(finalPoints.size());
    for (const QVector<double>& joints : finalPoints) {
        Point3D tcpPosition{};
        if (forwardKinematics(joints, tcpPosition)) {
            retainedPositions.append(tcpPosition);
        }
    }
    QApplication::restoreOverrideCursor();

    updateVisibilityPreview(retainedPositions);
    m_previewRetainedJointPoints = finalPoints;
    ui->exportPreviewPoseButton->setEnabled(
        !m_previewRetainedJointPoints.isEmpty());

    const int duplicateFilteredCount =
        generatedCount - candidatePoints.size();
    const QString regionStageText =
        useRegionFilter
            ? QStringLiteral("启用，移除 %1，剩余 %2")
                  .arg(regionFilteredCount)
                  .arg(regionRetainedPoints.size())
            : QStringLiteral("未启用，剩余 %1")
                  .arg(regionRetainedPoints.size());
    const QString trackerStageText =
        useTrackerFilter
            ? QStringLiteral("启用，移除 %1，剩余 %2")
                  .arg(trackerFilteredCount)
                  .arg(finalPoints.size())
            : QStringLiteral("未启用，剩余 %1")
                  .arg(finalPoints.size());

    ui->trackerResultLabel->setText(
        QStringLiteral(
            "最终筛选：保留 %1 点\n"
            "关节范围生成：%2 点　去重：移除 %3，剩余 %4　"
            "扩散区域过滤：%5　J6整周过滤：%6")
            .arg(finalPoints.size())
            .arg(generatedCount)
            .arg(duplicateFilteredCount)
            .arg(candidatePoints.size())
            .arg(regionStageText)
            .arg(trackerStageText));
}

// 测试功能：导出最近一次有效预览中保留关节点的五轴正解 TCP 位姿。
void TestPoints::exportPreviewRetainedPoses()
{
    if (m_previewRetainedJointPoints.isEmpty()) {
        QMessageBox::information(
            this, QStringLiteral("没有可导出的预览结果"),
            QStringLiteral(
                "请先点击“预览筛选”，并确保至少有一个绿色保留点。"));
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this,
        QStringLiteral("导出预览保留点正解位姿"),
        QStringLiteral("preview_retained_fk_pose.csv"),
        QStringLiteral("CSV 文件 (*.csv)"));
    if (fileName.isEmpty()) {
        return;
    }
    if (!fileName.endsWith(
            QStringLiteral(".csv"), Qt::CaseInsensitive)) {
        fileName.append(QStringLiteral(".csv"));
    }

    QFile csvFile(fileName);
    if (!csvFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(
            this, QStringLiteral("导出失败"),
            QStringLiteral("无法创建文件：\n%1").arg(fileName));
        return;
    }

    QTextStream csvOut(&csvFile);
    csvOut << QChar(0xFEFF);
    csvOut
        << "Point,J1,J2,J3,J4,J5,J6,"
           "X_mm,Y_mm,Z_mm,RX_deg,RY_deg,"
           "ZYX_RZ_deg,ZYX_RY_deg,ZYX_RX_deg\n";

    const double radiansToDegrees =
        180.0 / std::acos(-1.0);
    int exportedCount = 0;
    int failedCount = 0;
    for (int pointIndex = 0;
         pointIndex < m_previewRetainedJointPoints.size();
         ++pointIndex) {
        const QVector<double>& joints =
            m_previewRetainedJointPoints[pointIndex];
        Pose5D pose{};
        if (!forwardKinematicsPose(joints, pose)) {
            ++failedCount;
            continue;
        }

        double zyxZDegrees = 0.0;
        double zyxYDegrees = 0.0;
        double zyxXDegrees = 0.0;
        fixedXyToZyxDegrees(
            pose.rx, pose.ry,
            zyxZDegrees, zyxYDegrees, zyxXDegrees);

        csvOut << QStringLiteral("P%1").arg(pointIndex + 1);
        for (int jointIndex = 0; jointIndex < 6; ++jointIndex) {
            const double jointValue =
                jointIndex < joints.size()
                    ? joints[jointIndex]
                    : 0.0;
            csvOut << ',' << QString::number(
                jointValue, 'f', 6);
        }
        csvOut
            << ',' << QString::number(pose.position.x, 'f', 6)
            << ',' << QString::number(pose.position.y, 'f', 6)
            << ',' << QString::number(pose.position.z, 'f', 6)
            << ',' << QString::number(
                           pose.rx * radiansToDegrees, 'f', 6)
            << ',' << QString::number(
                           pose.ry * radiansToDegrees, 'f', 6)
            << ',' << QString::number(zyxZDegrees, 'f', 6)
            << ',' << QString::number(zyxYDegrees, 'f', 6)
            << ',' << QString::number(zyxXDegrees, 'f', 6)
            << '\n';
        ++exportedCount;
    }
    csvFile.close();

    QMessageBox::information(
        this, QStringLiteral("测试位姿已导出"),
        QStringLiteral(
            "已导出 %1 个预览保留点。\n"
            "坐标单位：mm；姿态单位：度。\n"
            "末尾三列为标准 ZYX（R=Rz·Ry·Rx）欧拉角。\n"
            "正解失败：%2 个。\n\n%3")
            .arg(exportedCount)
            .arg(failedCount)
            .arg(fileName));
}

// 校验参数、生成测试点，并按当前STL选区过滤后保存文件。
void TestPoints::on_pushButton_Confirm_clicked()
{
    QVector<QVector<double>> uniquePoints;
    int generatedCount = 0;
    QString inputError;
    if (!generateCandidatePointsFromUi(
            uniquePoints, generatedCount, inputError)) {
        QMessageBox::warning(
            this, QStringLiteral("错误"), inputError);
        return;
    }

    // 只有模型已经成功加载并且用户勾选复选框时才进行 STL 过滤。
    // 未加载模型时即使复选框状态异常，也直接按未过滤方式生成。
    const bool hasStlModel = m_stlPolyData != nullptr;
    const bool needFilter =
        hasStlModel && ui->checkBox_filter->isChecked();
    if (needFilter && !m_regionCenterValid) {
        QMessageBox::warning(
            this, QStringLiteral("扩散中心无效"),
            QStringLiteral(
                "当前扩散中心位于 STL 模型外部，请调整 X/Y/Z，"
                "或点击“恢复默认中心”。"));
        return;
    }

    const bool needTrackerVisibilityFilter =
        ui->trackerVisibilityCheckBox->isChecked();
    if (needTrackerVisibilityFilter && !m_trackerOriginValid) {
        QMessageBox::warning(
            this, QStringLiteral("缺少仪器位置"),
            QStringLiteral(
                "已经启用跟踪仪可见性筛选，请先点击“获取/刷新位置”。"));
        return;
    }
    if (needTrackerVisibilityFilter) {
        QString installationError;
        if (!validateReflectorInstallation(installationError)) {
            QMessageBox::warning(
                this, QStringLiteral("靶球安装参数无效"),
                installationError);
            return;
        }
    }

    const QString fileName = QFileDialog::getSaveFileName(
        this, QStringLiteral("保存测试点文件"), QString(),
        QStringLiteral("文本文件 (*.txt)"));
    if (fileName.isEmpty()) {
        return;
    }

    int regionFilteredCount = 0;
    const QVector<QVector<double>> regionFilteredPoints =
        needFilter
            ? filterUnreachablePoints(
                  uniquePoints, regionFilteredCount)
            : uniquePoints;

    int trackerFilteredCount = 0;
    QApplication::setOverrideCursor(Qt::WaitCursor);
    const QVector<QVector<double>> finalPoints =
        needTrackerVisibilityFilter
            ? filterTrackerVisiblePoints(
                  regionFilteredPoints, trackerFilteredCount)
            : regionFilteredPoints;
    QApplication::restoreOverrideCursor();

    generateTXTFile(fileName, finalPoints);
    generateCSVFile(fileName, finalPoints);
    generateJBRFile(fileName, finalPoints, finalPoints.size());

    QString csvFileName = fileName;
    csvFileName.replace(".txt", ".csv");
    QString jbrFileName = fileName;
    if (finalPoints.size() > 10000) {
        jbrFileName.replace(".txt", "_1.JBR ...");
    } else {
        jbrFileName.replace(".txt", ".JBR");
    }

    QString filterText;
    if (needFilter) {
        filterText =
            QStringLiteral("扩散区域已启用，移除 %1 个点")
                .arg(regionFilteredCount);
    } else if (hasStlModel) {
        filterText = QStringLiteral("已加载 STL，但未勾选过滤");
    } else {
        filterText = QStringLiteral("未加载 STL，不进行过滤");
    }

    const QString trackerFilterText =
        needTrackerVisibilityFilter
            ? QStringLiteral(
                  "已启用，检查独立主轴J6整周，移除 %1 个点")
                  .arg(trackerFilteredCount)
            : QStringLiteral("未启用");

    const QString resultInfo =
        QStringLiteral(
            "采样方式：打乱拉丁超立方\n"
            "生成点数：%1 点\n"
            "去重后：%2 点\n"
            "最终保留：%3 点\n"
            "STL 选区过滤：%4\n"
            "跟踪仪可见性筛选：%5\n\n"
            "已保存：\n- %6\n- %7\n- %8")
            .arg(generatedCount)
            .arg(uniquePoints.size())
            .arg(finalPoints.size())
            .arg(filterText)
            .arg(trackerFilterText)
            .arg(fileName)
            .arg(csvFileName)
            .arg(jbrFileName);

    QMessageBox::information(this, QStringLiteral("生成完成"), resultInfo);
    emit signal_path(csvFileName);
}

// 初始化机器人正解上下文和机构参数。
void TestPoints::initializeKinematicsContext()
{
    m_kinematicsContext = HK_CreateContext();
    if (!m_kinematicsContext)
    {
        qWarning() << "Failed to create kinematics context";
        return;
    }

    // 机构参数设置一次后复用，避免过滤大量测试点时重复创建正解上下文。
    const HK_RobotParameters params = createDefaultKinematicsParameters();
    const int ret = HK_SetRobotParameters(m_kinematicsContext, &params);
    if (ret != 0)
    {
        qWarning() << "Failed to set kinematics parameters, ret:" << ret;
    }
}

// 读取 STL 模型，建立表面颜色数据并初始化三维扩散中心。
bool TestPoints::loadSTLModel(const QString& filePath)
{
    QString readerPath = filePath;
    QTemporaryFile temporaryStl;
    bool hasNonAsciiPath = false;
    for (const QChar character : filePath) {
        if (character.unicode() > 0x7f) {
            hasNonAsciiPath = true;
            break;
        }
    }

    // VTK 9.1 的 STL 读取器在 Windows 下不能可靠处理中文路径，
    // 因此仅在需要时复制到纯英文临时文件后读取。
    if (hasNonAsciiPath) {
        QFile source(filePath);
        temporaryStl.setFileTemplate(
            QDir::tempPath() + QStringLiteral("/pcdmis-stl-XXXXXX.stl"));
        if (!source.open(QIODevice::ReadOnly) || !temporaryStl.open()) {
            return false;
        }

        while (!source.atEnd()) {
            const QByteArray block = source.read(1024 * 1024);
            if (block.isEmpty() || temporaryStl.write(block) != block.size()) {
                return false;
            }
        }
        temporaryStl.flush();
        readerPath = temporaryStl.fileName();
    }

    const auto reader = vtkSmartPointer<vtkSTLReader>::New();
    const QByteArray encodedPath = QFile::encodeName(readerPath);
    reader->SetFileName(encodedPath.constData());
    reader->Update();

    const vtkSmartPointer<vtkPolyData> polyData = reader->GetOutput();
    if (polyData == nullptr || polyData->GetNumberOfPoints() <= 0 || polyData->GetNumberOfCells() <= 0) {
        return false;
    }

    m_stlPolyData = polyData;
    m_stlFilePath = filePath;
    m_stlPolyData->GetBounds(m_stlBounds);

    // 坐标轴原点固定为 STL 的 (0, 0, 0)，长度随模型最大尺寸自动调整。
    const double xLength = m_stlBounds[1] - m_stlBounds[0];
    const double yLength = m_stlBounds[3] - m_stlBounds[2];
    const double zLength = m_stlBounds[5] - m_stlBounds[4];
    const double maxLength = qMax(xLength, qMax(yLength, zLength));
    m_regionHalfLengths[0] = qMax(xLength * 0.5, 1e-9);
    m_regionHalfLengths[1] = qMax(yLength * 0.5, 1e-9);
    m_regionHalfLengths[2] = qMax(zLength * 0.5, 1e-9);

    const double axisLength = maxLength > 0.0 ? maxLength * 0.25 : 1.0;
    m_axesActor->SetTotalLength(axisLength, axisLength, axisLength);
    m_axesActor->SetCylinderRadius(0.02);
    m_axesActor->SetConeRadius(0.08);
    m_axesActor->SetVisibility(true);

    const double centerMarkerRadius =
        maxLength > 0.0 ? maxLength * 0.012 : 1.0;
    m_centerSource->SetRadius(centerMarkerRadius);

    if (m_modelActor != nullptr) {
        m_renderer->RemoveActor(m_modelActor);
    }

    m_modelCellColors = vtkSmartPointer<vtkUnsignedCharArray>::New();
    m_modelCellColors->SetName("RegionColors");
    m_modelCellColors->SetNumberOfComponents(3);
    m_modelCellColors->SetNumberOfTuples(m_stlPolyData->GetNumberOfCells());
    const unsigned char normalColor[3] = {174, 180, 190};
    for (vtkIdType cellIndex = 0;
         cellIndex < m_stlPolyData->GetNumberOfCells();
         ++cellIndex) {
        m_modelCellColors->SetTypedTuple(cellIndex, normalColor);
    }
    m_stlPolyData->GetCellData()->SetScalars(m_modelCellColors);

    const auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(m_stlPolyData);
    mapper->SetScalarModeToUseCellData();
    mapper->SetColorModeToDirectScalars();
    mapper->ScalarVisibilityOn();

    m_modelActor = vtkSmartPointer<vtkActor>::New();
    m_modelActor->SetMapper(mapper);
    m_modelActor->GetProperty()->SetOpacity(0.68);
    m_modelActor->GetProperty()->EdgeVisibilityOn();
    m_modelActor->GetProperty()->SetEdgeColor(0.30, 0.33, 0.38);
    m_renderer->AddActor(m_modelActor);

    const Point3D defaultCenter = calculateDefaultRegionCenter();
    m_defaultRegionCenter[0] = defaultCenter.x;
    m_defaultRegionCenter[1] = defaultCenter.y;
    m_defaultRegionCenter[2] = defaultCenter.z;

    ui->stlPathLabel->setText(QFileInfo(filePath).fileName());
    ui->stlPathLabel->setToolTip(filePath);
    ui->regionGroupBox->setEnabled(true);
    ui->checkBox_filter->setChecked(true);
    resetRegion();
    updateTrackerVisualization();
    resetCamera();

    return true;
}

// 将一组关节值正解为TCP坐标，并明确返回计算是否成功。
bool TestPoints::forwardKinematics(const QVector<double>& jointValues,
                                   Point3D& tcpPosition)
{
    Pose5D pose{};
    if (!forwardKinematicsPose(jointValues, pose)) {
        tcpPosition = {0.0, 0.0, 0.0};
        return false;
    }

    tcpPosition = pose.position;
    return true;
}

// 返回五轴正解的完整 UI 位姿 [x,y,z,rx,ry]。
bool TestPoints::forwardKinematicsPose(
    const QVector<double>& jointValues, Pose5D& tcpPose)
{
    tcpPose = {{0.0, 0.0, 0.0}, 0.0, 0.0};
    if (jointValues.size() < 5) {
        qWarning() << "Forward kinematics requires at least 5 joint values:" << jointValues;
        return false;
    }

    if (!m_kinematicsContext) {
        qWarning() << "Forward kinematics context is not initialized";
        return false;
    }

    double joints[5] = {};
    for (int i = 0; i < 5; ++i) {
        joints[i] = jointValues[i];
    }

    ForwardResult result;
    const int ret =
        HK_ForwardKinematicsResult5Axis(m_kinematicsContext, joints, &result);

    if (ret == 0 && result.ok && result.uiPose.size() >= 5) {
        tcpPose.position.x = result.uiPose[0];
        tcpPose.position.y = result.uiPose[1];
        tcpPose.position.z = result.uiPose[2];
        tcpPose.rx = result.uiPose[3];
        tcpPose.ry = result.uiPose[4];
        return true;
    }

    qWarning() << "Forward kinematics failed, joints:" << jointValues
               << "return code:" << ret;
    return false;
}

// 判断TCP点是否位于原始STL封闭空间内部。
bool TestPoints::isPointInsideSTL(const Point3D& point)
{
    if (m_stlPolyData == nullptr) {
        return false;
    }

    vtkSmartPointer<vtkPoints> testPoints = vtkSmartPointer<vtkPoints>::New();
    testPoints->InsertNextPoint(point.x, point.y, point.z);

    vtkSmartPointer<vtkPolyData> testPolyData = vtkSmartPointer<vtkPolyData>::New();
    testPolyData->SetPoints(testPoints);

    vtkSmartPointer<vtkSelectEnclosedPoints> selectEnclosedPoints =
        vtkSmartPointer<vtkSelectEnclosedPoints>::New();
    selectEnclosedPoints->SetSurfaceData(m_stlPolyData);
    selectEnclosedPoints->SetInputData(testPolyData);
    selectEnclosedPoints->Update();

    return selectEnclosedPoints->IsInside(0) != 0;
}

// 判断 TCP 点是否位于当前中心和范围定义的三维扩散区域内。
bool TestPoints::isPointInsideSelectedRegion(const Point3D& point) const
{
    return m_regionCenterValid
        && normalizedRegionDistance(point) <= m_regionThreshold;
}

// 正解测试点，并仅保留同时位于选区和STL内部的关节值。
QVector<QVector<double>> TestPoints::filterUnreachablePoints(const QVector<QVector<double>>& allPoints,
                                                             int& filteredCount)
{
    QVector<QVector<double>> validPoints;
    validPoints.reserve(allPoints.size());
    filteredCount = 0;

    for (int i = 0; i < allPoints.size(); ++i) {
        const QVector<double>& point = allPoints[i];
        Point3D tcpPosition{};
        const bool keep = forwardKinematics(point, tcpPosition)
            && isPointInsideSelectedRegion(tcpPosition)
            && isPointInsideSTL(tcpPosition);
        if (keep) {
            validPoints.append(point);
        } else {
            ++filteredCount;
        }

        if ((i + 1) % 100 == 0) {
            qDebug() << "STL region filter:" << (i + 1)
                     << "/" << allPoints.size();
        }
    }

    qDebug() << "STL region filter done, kept:" << validPoints.size()
             << "removed:" << filteredCount;
    return validPoints;
}

// 检查靶球安装参数。径向开口需要一个非零的 TCP 到靶球向量。
bool TestPoints::validateReflectorInstallation(
    QString& errorMessage) const
{
    errorMessage.clear();
    if (ui->reflectorAxisComboBox->currentIndex() > 1) {
        return true;
    }

    const double offsetX = ui->reflectorOffsetXSpinBox->value();
    const double offsetY = ui->reflectorOffsetYSpinBox->value();
    const double offsetZ = ui->reflectorOffsetZSpinBox->value();
    const double offsetLength = std::sqrt(
        offsetX * offsetX +
        offsetY * offsetY +
        offsetZ * offsetZ);
    if (offsetLength > 1.0e-9) {
        return true;
    }

    errorMessage = QStringLiteral(
        "当前开口方向使用“TCP 与靶球之间的径向”，"
        "但靶球相对 TCP 的 X/Y/Z 偏移全部为 0。\n"
        "请输入实际安装偏移，或选择明确的 TCP ±X/±Y/±Z 开口方向。");
    return false;
}

// 保持 J1～J5 的正解位姿不变，模拟独立主轴 J6 带动靶球绕 TCP +Z 轴旋转一周。
bool TestPoints::isVisibleForFullRotation(
    const QVector<double>& jointValues)
{
    if (!m_trackerOriginValid || jointValues.size() < 5) {
        return false;
    }

    Pose5D displayPose{};
    if (!forwardKinematicsPose(jointValues, displayPose)) {
        return false;
    }

    const double localOffsetAtZero[3] = {
        ui->reflectorOffsetXSpinBox->value(),
        ui->reflectorOffsetYSpinBox->value(),
        ui->reflectorOffsetZSpinBox->value()
    };

    double localNormalAtZero[3] = {0.0, 0.0, 1.0};
    switch (ui->reflectorAxisComboBox->currentIndex()) {
    case 0:
    case 1: {
        const double offsetLength = std::sqrt(
            localOffsetAtZero[0] * localOffsetAtZero[0] +
            localOffsetAtZero[1] * localOffsetAtZero[1] +
            localOffsetAtZero[2] * localOffsetAtZero[2]);
        if (offsetLength <= 1.0e-9) {
            return false;
        }
        const double direction =
            ui->reflectorAxisComboBox->currentIndex() == 0
                ? 1.0
                : -1.0;
        for (int axis = 0; axis < 3; ++axis) {
            localNormalAtZero[axis] =
                direction * localOffsetAtZero[axis] / offsetLength;
        }
        break;
    }
    case 2:
        break;
    case 3:
        localNormalAtZero[2] = -1.0;
        break;
    case 4:
        localNormalAtZero[0] = 1.0;
        localNormalAtZero[2] = 0.0;
        break;
    case 5:
        localNormalAtZero[0] = -1.0;
        localNormalAtZero[2] = 0.0;
        break;
    case 6:
        localNormalAtZero[1] = 1.0;
        localNormalAtZero[2] = 0.0;
        break;
    case 7:
        localNormalAtZero[1] = -1.0;
        localNormalAtZero[2] = 0.0;
        break;
    default:
        break;
    }

    // 五轴正解在整周计算中只调用一次。J6 是独立主轴，不属于这五个定位关节。
    const double rx = displayPose.rx;
    const double ry = displayPose.ry;
    const double sinX = std::sin(rx);
    const double cosX = std::cos(rx);
    const double sinY = std::sin(ry);
    const double cosY = std::cos(ry);

    const auto tcpLocalToBase =
        [sinX, cosX, sinY, cosY](const double local[3],
                                 double base[3]) {
            // 运动学五轴姿态为 R=Rx(rx)*Ry(ry)：
            // 对局部向量先应用 Ry，再应用 Rx。
            const double afterY[3] = {
                cosY * local[0] + sinY * local[2],
                local[1],
                -sinY * local[0] + cosY * local[2]
            };
            base[0] = afterY[0];
            base[1] =
                cosX * afterY[1] - sinX * afterY[2];
            base[2] =
                sinX * afterY[1] + cosX * afterY[2];
        };

    const double pi = std::acos(-1.0);
    const double maximumIncidenceRadians =
        ui->incidenceAngleSpinBox->value() * pi / 180.0;
    const double minimumDot = std::cos(maximumIncidenceRadians);
    const int requestedStep = ui->rotationStepSpinBox->value();
    const int sampleCount =
        qMax(1, static_cast<int>(std::ceil(360.0 / requestedStep)));

    for (int sampleIndex = 0;
         sampleIndex < sampleCount;
         ++sampleIndex) {
        const double j6Radians =
            2.0 * pi * sampleIndex / sampleCount;
        const double sinJ6 = std::sin(j6Radians);
        const double cosJ6 = std::cos(j6Radians);

        // J6 绕 TCP 局部 +Z 轴转动：靶球中心偏移和开口法向同步旋转。
        const double rotatedLocalOffset[3] = {
            cosJ6 * localOffsetAtZero[0] -
                sinJ6 * localOffsetAtZero[1],
            sinJ6 * localOffsetAtZero[0] +
                cosJ6 * localOffsetAtZero[1],
            localOffsetAtZero[2]
        };
        const double rotatedLocalNormal[3] = {
            cosJ6 * localNormalAtZero[0] -
                sinJ6 * localNormalAtZero[1],
            sinJ6 * localNormalAtZero[0] +
                cosJ6 * localNormalAtZero[1],
            localNormalAtZero[2]
        };

        double offsetInBase[3] = {};
        double normalInBase[3] = {};
        tcpLocalToBase(rotatedLocalOffset, offsetInBase);
        tcpLocalToBase(rotatedLocalNormal, normalInBase);

        const Point3D reflectorPosition = {
            displayPose.position.x + offsetInBase[0],
            displayPose.position.y + offsetInBase[1],
            displayPose.position.z + offsetInBase[2]
        };

        const double toTrackerX =
            m_trackerOrigin[0] - reflectorPosition.x;
        const double toTrackerY =
            m_trackerOrigin[1] - reflectorPosition.y;
        const double toTrackerZ =
            m_trackerOrigin[2] - reflectorPosition.z;
        const double distance = std::sqrt(
            toTrackerX * toTrackerX +
            toTrackerY * toTrackerY +
            toTrackerZ * toTrackerZ);
        if (distance < kTrackerMinimumDistanceMm ||
            distance > kTrackerMaximumDistanceMm) {
            return false;
        }

        const double dot = qBound(
            -1.0,
            (normalInBase[0] * toTrackerX +
             normalInBase[1] * toTrackerY +
             normalInBase[2] * toTrackerZ) / distance,
            1.0);
        if (dot < minimumDot) {
            return false;
        }
    }

    return true;
}

// 对候选点应用跟踪仪 J6 整周可见性规则。
QVector<QVector<double>> TestPoints::filterTrackerVisiblePoints(
    const QVector<QVector<double>>& allPoints,
    int& filteredCount)
{
    QVector<QVector<double>> visiblePoints;
    visiblePoints.reserve(allPoints.size());
    filteredCount = 0;

    for (int pointIndex = 0;
         pointIndex < allPoints.size();
         ++pointIndex) {
        const bool visible = isVisibleForFullRotation(
            allPoints[pointIndex]);
        if (visible) {
            visiblePoints.append(allPoints[pointIndex]);
        } else {
            ++filteredCount;
        }

        if ((pointIndex + 1) % 50 == 0) {
            QApplication::processEvents(
                QEventLoop::ExcludeUserInputEvents);
        }
    }

    qDebug() << "Tracker visibility filter done, kept:"
             << visiblePoints.size()
             << "removed:" << filteredCount;
    return visiblePoints;
}

// 使用打乱后的拉丁超立方在各关节范围内生成指定数量的测试点。
QVector<QVector<double>> TestPoints::generateAllTestPoints(const double j_min[6], const double j_max[6],
                                                           const QVector<int>& validJoints, int count,
                                                           bool allowDecimal)
{
    QVector<QVector<double>> allPoints;
    allPoints.reserve(count);

    // 固定随机种子使相同输入每次都得到相同结果，保证预览和文件输出一致。
    std::mt19937 randomGenerator(20260728u);
    QSet<QString> seenPoints;
    constexpr int maximumAttempts = 32;

    // 整数或0.5精度可能让不同采样点变成相同值。
    // 出现重复时重新打乱各关节分段，补足用户要求的唯一点数量。
    for (int attempt = 0;
         attempt < maximumAttempts && allPoints.size() < count;
         ++attempt) {
        QVector<QVector<int>> segmentOrders(6);

        // 每个有效关节都使用全部N个分段，并独立打乱分段顺序。
        for (int joint : validJoints) {
            segmentOrders[joint].resize(count);
            std::iota(
                segmentOrders[joint].begin(),
                segmentOrders[joint].end(), 0);
            std::shuffle(
                segmentOrders[joint].begin(),
                segmentOrders[joint].end(), randomGenerator);
        }

        for (int pointIndex = 0;
             pointIndex < count && allPoints.size() < count;
             ++pointIndex) {
            QVector<double> point(6);

            // 不参与变化的关节保持最小值，J6仍固定为0°。
            for (int joint = 0; joint < 6; ++joint) {
                point[joint] =
                    generatedPointValue(j_min[joint], allowDecimal);
            }

            // 在各分段中点取值；独立乱序避免多个关节沿同一比例同步变化。
            for (int joint : validJoints) {
                const int segment = segmentOrders[joint][pointIndex];
                const double ratio =
                    (static_cast<double>(segment) + 0.5) / count;
                const double value =
                    j_min[joint] +
                    ratio * (j_max[joint] - j_min[joint]);
                point[joint] =
                    generatedPointValue(value, allowDecimal);
            }

            QString key;
            for (int joint = 0; joint < point.size(); ++joint) {
                if (joint > 0) {
                    key.append(',');
                }
                key.append(pointKeyValue(point[joint]));
            }
            if (seenPoints.contains(key)) {
                continue;
            }

            seenPoints.insert(key);
            allPoints.append(point);
        }
    }

    return allPoints;
}

// 删除关节值完全相同的重复测试点。
QVector<QVector<double>> TestPoints::removeDuplicatePoints(const QVector<QVector<double>>& allPoints)
{
    QVector<QVector<double>> uniquePoints;
    QSet<QString> seenPoints;
    uniquePoints.reserve(allPoints.size());

    for (const QVector<double>& point : allPoints) {
        QString key;
        key.reserve(64);

        // 用六个关节值拼出唯一键，去掉大数量插值后产生的重复点
        for (int i = 0; i < point.size(); ++i) {
            if (i > 0) {
                key.append(',');
            }
            key.append(pointKeyValue(point[i]));
        }

        if (seenPoints.contains(key)) {
            continue;
        }

        seenPoints.insert(key);
        uniquePoints.append(point);
    }

    return uniquePoints;
}

// 将测试点写入 TXT 文件。
void TestPoints::generateTXTFile(const QString& fileName, const QVector<QVector<double>>& allPoints)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法创建TXT文件！");
        return;
    }

    QTextStream out(&file);

    // 写入所有点数据（整数格式）
    for (int i = 0; i < allPoints.size(); i++) {
        const QVector<double>& point = allPoints[i];
        QString pointName = QString("P%1").arg(i + 1);
        out << QString("%1 %2 %3 %4 %5 %6 %7\n")
               .arg(pointName)
               .arg(formatPointValue(point[0]))
               .arg(formatPointValue(point[1]))
               .arg(formatPointValue(point[2]))
               .arg(formatPointValue(point[3]))
               .arg(formatPointValue(point[4]))
               .arg(formatPointValue(point[5]));
    }

    file.close();
}

// 将测试点写入 CSV 文件。
void TestPoints::generateCSVFile(const QString& baseFileName, const QVector<QVector<double>>& allPoints)
{
    QString csvFileName = baseFileName;
    csvFileName.replace(".txt", ".csv");

    QFile csvFile(csvFileName);
    if (!csvFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法创建CSV文件！");
        return;
    }

    QTextStream csvOut(&csvFile);

    // 写入CSV表头
    csvOut << "点名,J1,J2,J3,J4,J5,J6, ,X,Y,Z,I,J,K\n";

    // 写入所有点数据
    for (int i = 0; i < allPoints.size(); i++) {
        const QVector<double>& point = allPoints[i];
        QString pointName = QString("P%1").arg(i + 1);
        csvOut << QString("%1,%2,%3,%4,%5,%6,%7\n")
               .arg(pointName)
               .arg(formatPointValue(point[0]))
               .arg(formatPointValue(point[1]))
               .arg(formatPointValue(point[2]))
               .arg(formatPointValue(point[3]))
               .arg(formatPointValue(point[4]))
               .arg(formatPointValue(point[5]));
    }

    csvFile.close();
}

// 将测试点写入机器人 JBR 文件。
void TestPoints::generateJBRFile(const QString& baseFileName, const QVector<QVector<double>>& allPoints, int totalPoints)
{
    const int maxPointsPerFile = 10000;
    if (totalPoints > maxPointsPerFile) {
        int fileCount = (totalPoints + maxPointsPerFile - 1) / maxPointsPerFile;
        for (int fileIndex = 0; fileIndex < fileCount; fileIndex++) {
            int startIndex = fileIndex * maxPointsPerFile;
            int currentPoints = qMin(maxPointsPerFile, totalPoints - startIndex);

            QVector<QVector<double>> partPoints;
            partPoints.reserve(currentPoints);
            for (int i = 0; i < currentPoints; i++) {
                partPoints.append(allPoints[startIndex + i]);
            }

            QString partBaseFileName = baseFileName;
            partBaseFileName.replace(".txt", QString("_%1.txt").arg(fileIndex + 1));
            generateJBRFile(partBaseFileName, partPoints, currentPoints);
        }
        return;
    }

    QString jbrFileName = baseFileName;
    jbrFileName.replace(".txt", ".JBR");

    QFile jbrFile(jbrFileName);
    if (!jbrFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法创建JBR文件！");
        return;
    }

    QTextStream jbrOut(&jbrFile);

    // 写入文件头
    jbrOut << "//DIR\n";
    jbrOut << "//JOB\n";
    jbrOut << "//NAME DR8_23_11_0_0\n";
    jbrOut << "//POS\n";
    jbrOut << QString("///NPOS %1,0,0,0,0,0\n").arg(totalPoints);
    jbrOut << "///POSTYPE PULSE\n";
    jbrOut << "///PULSE\n";

    // 将五轴关节值写入JBR点位段。
    for (int i = 0; i < allPoints.size(); i++) {
        const QVector<double>& point = allPoints[i];
        const double j4 = point[3];
        const double j5 = point[4];

        jbrOut << QString("P%1 = 0.0,0.0,0.0,0.0,0.0,0.0,0.0,%2,%3,%4,%5,%6,1.0000,0.0\n")
                      .arg(i + 1, 5, 10, QChar('0'))
                      .arg(static_cast<double>(point[0]), 0, 'f', 4)
                      .arg(static_cast<double>(point[1]), 0, 'f', 4)
                      .arg(static_cast<double>(point[2]), 0, 'f', 4)
                      .arg(j4, 0, 'f', 4)
                      .arg(j5, 0, 'f', 4);
    }

    // 写入指令部分
    jbrOut << "//INSTRUCTION\n";
    jbrOut << "///DATE 2025.10.11 14:39:33\n";
    jbrOut << "ROBOTTYPE = [FIVE_AXLE_MIXED]\n";
    jbrOut << "DOUBLEROBOT = [NoCooperative]\n";
    jbrOut << "EXTGROUPTYPE = [LineDouble,SpinSingle,None]\n";//奇瑞
    //jbrOut << "EXTGROUPTYPE = [LineSingle,SpinSingle,None]\n";//焊接版850
    //jbrOut << "EXTGROUPTYPE = [LineTriple,SpinSingle,None]\n";//中兵
    jbrOut << "PROVERSION = [1.0.6]\n";
    jbrOut << "NOP\n";
    jbrOut << "SWITCHTOOL(0)\n";
    jbrOut << "SWITCHUSER(0)\n";
    jbrOut << "CLKRESET ID = 10\n";
    jbrOut << "SET GD005 = 0\n";
    jbrOut << "CLKSTART ID = 10 GD005\n";
    //jbrOut << "MOVJ P0001 V = GI002 PL = 5 ACC = GI008 DEC = GI009 0\n";

    // 写入所有点的MOVL指令
    for (int i = 0; i < totalPoints; i++) {
        jbrOut << QString("MOVJ P%1 VJ = 100 % PL = 0 ACC = 100 DEC = 100 0\n")
                  .arg(i + 1, 5, 10, QChar('0'));
        // jbrOut << "TIMER T = 0.25\n";
        // jbrOut << "DOUT OT#(10) 1 T = 0 0\n";
        // jbrOut << "TIMER T = 0.25\n";
        // jbrOut << "WAIT {(DOUT10 == 0)}\n";

        //jbrOut << "PAUSERUN ALL\n";
        //jbrOut << "TIMER T = 5\n";

    }

    jbrOut << "CLKSTOP ID = 10\n";
    jbrOut << "END\n";

    jbrFile.close();
}
