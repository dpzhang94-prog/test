#include "mainwindow.h"
#include "features/testpoints/testpoints.h"
#include "pcdmisclient.h"
#include "tcpserverworker.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QHeaderView>
#include <QMetaObject>
#include <QMessageBox>
#include <QStatusBar>
#include <QTableWidgetItem>
#include <QThread>

#include <array>
#include <set>

namespace {
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
    connect(m_tcpWorker, &TcpServerWorker::serverStateChanged,
            this, &MainWindow::showTcpServerState,
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

    m_circleCapturePending = false;
    m_pendingCircleCaptureId = 0;
    ui->captureCirclePointButton->setEnabled(m_client->isConnected());

    if (!success) {
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
        QMessageBox::information(
            this, QStringLiteral("坐标系已切换"),
            QStringLiteral("读取期间坐标系发生变化，本次结果未采集，请重新操作。"));
        return;
    }
    if (!m_circlePoints.empty() &&
        currentMode != m_circlePointCoordinateMode) {
        QMessageBox::information(
            this, QStringLiteral("坐标系不一致"),
            QStringLiteral(
                "已有采集点来自另一个坐标系。请先清空采集点，"
                "再使用当前坐标系重新采集。"));
        return;
    }
    if (!m_hasTrackerOrigin) {
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
    m_circlePoints.clear();
    m_circlePointCoordinateMode = -1;
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
    if (!m_hasTrackerOrigin) {
        QMessageBox::information(
            this, QStringLiteral("无法计算"),
            QStringLiteral("尚未取得激光跟踪仪在当前坐标系中的位置。"));
        return;
    }

    const CircleFitResult result =
        GeometryCalculator::fitCircle(m_circlePoints, m_trackerOrigin);
    if (!result.success) {
        QMessageBox::information(
            this, QStringLiteral("计算失败"), result.errorMessage);
        return;
    }

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
    // 圆周采集正在等待工作线程返回时保持禁用，避免重复提交请求。
    ui->captureCirclePointButton->setEnabled(
        connected && !m_circleCapturePending);

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
    ui->calculateCircleButton->setEnabled(m_circlePoints.size() >= 3);
    ui->deleteCirclePointButton->setEnabled(!m_circlePoints.empty());
    ui->clearCirclePointsButton->setEnabled(!m_circlePoints.empty());
}

void MainWindow::showCircleResult(const CircleFitResult &result)
{
    ui->circleResultTable->setRowCount(1);
    const std::array<double, 10> values{
        result.center.x, result.center.y, result.center.z,
        result.angleA, result.angleB, result.angleC,
        result.radius, result.planeRms,
        result.circleRms, result.maximumResidual
    };
    for (int column = 0;
         column < static_cast<int>(values.size()); ++column) {
        ui->circleResultTable->setItem(
            0, column,
            numberItem(values[static_cast<std::size_t>(column)]));
    }

    ui->circleResultTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);
    ui->circleResultTable->horizontalHeader()->setStretchLastSection(false);
}
