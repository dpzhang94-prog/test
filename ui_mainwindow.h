/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QGroupBox *connectionGroupBox;
    QGridLayout *connectionLayout;
    QLabel *progIdTitleLabel;
    QLineEdit *progIdEdit;
    QCheckBox *visibleCheckBox;
    QPushButton *connectButton;
    QPushButton *disconnectButton;
    QLabel *automationTitleLabel;
    QLabel *automationStatusLabel;
    QGroupBox *readGroupBox;
    QVBoxLayout *readLayout;
    QHBoxLayout *controlLayout;
    QLabel *coordinateModeTitleLabel;
    QComboBox *coordinateModeComboBox;
    QLabel *intervalTitleLabel;
    QSpinBox *intervalSpinBox;
    QPushButton *readOnceButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QSpacerItem *controlSpacer;
    QFrame *coordinateFrame;
    QGridLayout *coordinateLayout;
    QLabel *xTitleLabel;
    QLabel *yTitleLabel;
    QLabel *zTitleLabel;
    QLabel *xValueLabel;
    QLabel *yValueLabel;
    QLabel *zValueLabel;
    QLabel *coordinateSystemLabel;
    QLabel *sampleTimeTitleLabel;
    QLabel *sampleTimeLabel;
    QGroupBox *circleFitGroupBox;
    QVBoxLayout *circleFitLayout;
    QHBoxLayout *circleButtonLayout;
    QLabel *circlePointCountLabel;
    QSpacerItem *circleButtonSpacer;
    QPushButton *captureCirclePointButton;
    QPushButton *deleteCirclePointButton;
    QPushButton *clearCirclePointsButton;
    QPushButton *calculateCircleButton;
    QHBoxLayout *circleTablesLayout;
    QVBoxLayout *circlePointsLayout;
    QLabel *circlePointsTitleLabel;
    QTableWidget *circlePointsTable;
    QVBoxLayout *circleResultLayout;
    QLabel *circleResultDescriptionLabel;
    QTableWidget *circleResultTable;
    QGroupBox *toolsGroupBox;
    QHBoxLayout *toolsLayout;
    QLabel *testPointsDescriptionLabel;
    QSpacerItem *toolsSpacer;
    QPushButton *testPointsButton;
    QGroupBox *tcpServerGroupBox;
    QHBoxLayout *tcpServerLayout;
    QLabel *tcpServerStatusLabel;
    QSpacerItem *tcpServerSpacer;
    QPushButton *startTcpServerButton;
    QPushButton *stopTcpServerButton;
    QGroupBox *logGroupBox;
    QVBoxLayout *logLayout;
    QPlainTextEdit *logEdit;
    QHBoxLayout *logButtonLayout;
    QSpacerItem *logSpacer;
    QPushButton *clearLogButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(982, 830);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(16, 16, 16, 16);
        connectionGroupBox = new QGroupBox(centralwidget);
        connectionGroupBox->setObjectName("connectionGroupBox");
        connectionLayout = new QGridLayout(connectionGroupBox);
        connectionLayout->setObjectName("connectionLayout");
        progIdTitleLabel = new QLabel(connectionGroupBox);
        progIdTitleLabel->setObjectName("progIdTitleLabel");

        connectionLayout->addWidget(progIdTitleLabel, 0, 0, 1, 1);

        progIdEdit = new QLineEdit(connectionGroupBox);
        progIdEdit->setObjectName("progIdEdit");
        progIdEdit->setReadOnly(true);

        connectionLayout->addWidget(progIdEdit, 0, 1, 1, 1);

        visibleCheckBox = new QCheckBox(connectionGroupBox);
        visibleCheckBox->setObjectName("visibleCheckBox");
        visibleCheckBox->setChecked(true);

        connectionLayout->addWidget(visibleCheckBox, 0, 2, 1, 1);

        connectButton = new QPushButton(connectionGroupBox);
        connectButton->setObjectName("connectButton");

        connectionLayout->addWidget(connectButton, 0, 3, 1, 1);

        disconnectButton = new QPushButton(connectionGroupBox);
        disconnectButton->setObjectName("disconnectButton");

        connectionLayout->addWidget(disconnectButton, 0, 4, 1, 1);

        automationTitleLabel = new QLabel(connectionGroupBox);
        automationTitleLabel->setObjectName("automationTitleLabel");

        connectionLayout->addWidget(automationTitleLabel, 1, 0, 1, 1);

        automationStatusLabel = new QLabel(connectionGroupBox);
        automationStatusLabel->setObjectName("automationStatusLabel");

        connectionLayout->addWidget(automationStatusLabel, 1, 1, 1, 4);


        mainLayout->addWidget(connectionGroupBox);

        readGroupBox = new QGroupBox(centralwidget);
        readGroupBox->setObjectName("readGroupBox");
        readLayout = new QVBoxLayout(readGroupBox);
        readLayout->setObjectName("readLayout");
        controlLayout = new QHBoxLayout();
        controlLayout->setObjectName("controlLayout");
        coordinateModeTitleLabel = new QLabel(readGroupBox);
        coordinateModeTitleLabel->setObjectName("coordinateModeTitleLabel");

        controlLayout->addWidget(coordinateModeTitleLabel);

        coordinateModeComboBox = new QComboBox(readGroupBox);
        coordinateModeComboBox->addItem(QString());
        coordinateModeComboBox->addItem(QString());
        coordinateModeComboBox->setObjectName("coordinateModeComboBox");

        controlLayout->addWidget(coordinateModeComboBox);

        intervalTitleLabel = new QLabel(readGroupBox);
        intervalTitleLabel->setObjectName("intervalTitleLabel");

        controlLayout->addWidget(intervalTitleLabel);

        intervalSpinBox = new QSpinBox(readGroupBox);
        intervalSpinBox->setObjectName("intervalSpinBox");
        intervalSpinBox->setMinimum(20);
        intervalSpinBox->setMaximum(5000);
        intervalSpinBox->setSingleStep(20);
        intervalSpinBox->setValue(100);

        controlLayout->addWidget(intervalSpinBox);

        readOnceButton = new QPushButton(readGroupBox);
        readOnceButton->setObjectName("readOnceButton");

        controlLayout->addWidget(readOnceButton);

        startButton = new QPushButton(readGroupBox);
        startButton->setObjectName("startButton");

        controlLayout->addWidget(startButton);

        stopButton = new QPushButton(readGroupBox);
        stopButton->setObjectName("stopButton");

        controlLayout->addWidget(stopButton);

        controlSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        controlLayout->addItem(controlSpacer);


        readLayout->addLayout(controlLayout);

        coordinateFrame = new QFrame(readGroupBox);
        coordinateFrame->setObjectName("coordinateFrame");
        coordinateFrame->setFrameShape(QFrame::StyledPanel);
        coordinateLayout = new QGridLayout(coordinateFrame);
        coordinateLayout->setObjectName("coordinateLayout");
        xTitleLabel = new QLabel(coordinateFrame);
        xTitleLabel->setObjectName("xTitleLabel");
        xTitleLabel->setAlignment(Qt::AlignCenter);

        coordinateLayout->addWidget(xTitleLabel, 0, 0, 1, 1);

        yTitleLabel = new QLabel(coordinateFrame);
        yTitleLabel->setObjectName("yTitleLabel");
        yTitleLabel->setAlignment(Qt::AlignCenter);

        coordinateLayout->addWidget(yTitleLabel, 0, 1, 1, 1);

        zTitleLabel = new QLabel(coordinateFrame);
        zTitleLabel->setObjectName("zTitleLabel");
        zTitleLabel->setAlignment(Qt::AlignCenter);

        coordinateLayout->addWidget(zTitleLabel, 0, 2, 1, 1);

        xValueLabel = new QLabel(coordinateFrame);
        xValueLabel->setObjectName("xValueLabel");
        xValueLabel->setStyleSheet(QString::fromUtf8("font: 700 18pt \"Consolas\"; color: #005fb8;"));
        xValueLabel->setAlignment(Qt::AlignCenter);

        coordinateLayout->addWidget(xValueLabel, 1, 0, 1, 1);

        yValueLabel = new QLabel(coordinateFrame);
        yValueLabel->setObjectName("yValueLabel");
        yValueLabel->setStyleSheet(QString::fromUtf8("font: 700 18pt \"Consolas\"; color: #005fb8;"));
        yValueLabel->setAlignment(Qt::AlignCenter);

        coordinateLayout->addWidget(yValueLabel, 1, 1, 1, 1);

        zValueLabel = new QLabel(coordinateFrame);
        zValueLabel->setObjectName("zValueLabel");
        zValueLabel->setStyleSheet(QString::fromUtf8("font: 700 18pt \"Consolas\"; color: #005fb8;"));
        zValueLabel->setAlignment(Qt::AlignCenter);

        coordinateLayout->addWidget(zValueLabel, 1, 2, 1, 1);

        coordinateSystemLabel = new QLabel(coordinateFrame);
        coordinateSystemLabel->setObjectName("coordinateSystemLabel");
        coordinateSystemLabel->setAlignment(Qt::AlignCenter);

        coordinateLayout->addWidget(coordinateSystemLabel, 2, 0, 1, 3);

        sampleTimeTitleLabel = new QLabel(coordinateFrame);
        sampleTimeTitleLabel->setObjectName("sampleTimeTitleLabel");
        sampleTimeTitleLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        coordinateLayout->addWidget(sampleTimeTitleLabel, 3, 0, 1, 1);

        sampleTimeLabel = new QLabel(coordinateFrame);
        sampleTimeLabel->setObjectName("sampleTimeLabel");

        coordinateLayout->addWidget(sampleTimeLabel, 3, 1, 1, 2);


        readLayout->addWidget(coordinateFrame);


        mainLayout->addWidget(readGroupBox);

        circleFitGroupBox = new QGroupBox(centralwidget);
        circleFitGroupBox->setObjectName("circleFitGroupBox");
        circleFitLayout = new QVBoxLayout(circleFitGroupBox);
        circleFitLayout->setObjectName("circleFitLayout");
        circleButtonLayout = new QHBoxLayout();
        circleButtonLayout->setObjectName("circleButtonLayout");
        circlePointCountLabel = new QLabel(circleFitGroupBox);
        circlePointCountLabel->setObjectName("circlePointCountLabel");

        circleButtonLayout->addWidget(circlePointCountLabel);

        circleButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        circleButtonLayout->addItem(circleButtonSpacer);

        captureCirclePointButton = new QPushButton(circleFitGroupBox);
        captureCirclePointButton->setObjectName("captureCirclePointButton");

        circleButtonLayout->addWidget(captureCirclePointButton);

        deleteCirclePointButton = new QPushButton(circleFitGroupBox);
        deleteCirclePointButton->setObjectName("deleteCirclePointButton");

        circleButtonLayout->addWidget(deleteCirclePointButton);

        clearCirclePointsButton = new QPushButton(circleFitGroupBox);
        clearCirclePointsButton->setObjectName("clearCirclePointsButton");

        circleButtonLayout->addWidget(clearCirclePointsButton);

        calculateCircleButton = new QPushButton(circleFitGroupBox);
        calculateCircleButton->setObjectName("calculateCircleButton");

        circleButtonLayout->addWidget(calculateCircleButton);


        circleFitLayout->addLayout(circleButtonLayout);

        circleTablesLayout = new QHBoxLayout();
        circleTablesLayout->setObjectName("circleTablesLayout");
        circlePointsLayout = new QVBoxLayout();
        circlePointsLayout->setObjectName("circlePointsLayout");
        circlePointsTitleLabel = new QLabel(circleFitGroupBox);
        circlePointsTitleLabel->setObjectName("circlePointsTitleLabel");

        circlePointsLayout->addWidget(circlePointsTitleLabel);

        circlePointsTable = new QTableWidget(circleFitGroupBox);
        if (circlePointsTable->columnCount() < 4)
            circlePointsTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        circlePointsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        circlePointsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        circlePointsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        circlePointsTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        circlePointsTable->setObjectName("circlePointsTable");
        circlePointsTable->setMinimumSize(QSize(200, 120));
        circlePointsTable->setMaximumSize(QSize(410, 170));
        circlePointsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        circlePointsTable->setAlternatingRowColors(true);

        circlePointsLayout->addWidget(circlePointsTable);


        circleTablesLayout->addLayout(circlePointsLayout);

        circleResultLayout = new QVBoxLayout();
        circleResultLayout->setObjectName("circleResultLayout");
        circleResultDescriptionLabel = new QLabel(circleFitGroupBox);
        circleResultDescriptionLabel->setObjectName("circleResultDescriptionLabel");

        circleResultLayout->addWidget(circleResultDescriptionLabel);

        circleResultTable = new QTableWidget(circleFitGroupBox);
        if (circleResultTable->columnCount() < 10)
            circleResultTable->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        circleResultTable->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        circleResultTable->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        circleResultTable->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        circleResultTable->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        circleResultTable->setHorizontalHeaderItem(4, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        circleResultTable->setHorizontalHeaderItem(5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        circleResultTable->setHorizontalHeaderItem(6, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        circleResultTable->setHorizontalHeaderItem(7, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        circleResultTable->setHorizontalHeaderItem(8, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        circleResultTable->setHorizontalHeaderItem(9, __qtablewidgetitem13);
        circleResultTable->setObjectName("circleResultTable");
        circleResultTable->setMinimumSize(QSize(0, 120));
        circleResultTable->setMaximumSize(QSize(16777215, 170));
        circleResultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        circleResultTable->setSelectionMode(QAbstractItemView::NoSelection);

        circleResultLayout->addWidget(circleResultTable);


        circleTablesLayout->addLayout(circleResultLayout);

        circleTablesLayout->setStretch(0, 4);
        circleTablesLayout->setStretch(1, 6);

        circleFitLayout->addLayout(circleTablesLayout);


        mainLayout->addWidget(circleFitGroupBox);

        toolsGroupBox = new QGroupBox(centralwidget);
        toolsGroupBox->setObjectName("toolsGroupBox");
        toolsLayout = new QHBoxLayout(toolsGroupBox);
        toolsLayout->setObjectName("toolsLayout");
        testPointsDescriptionLabel = new QLabel(toolsGroupBox);
        testPointsDescriptionLabel->setObjectName("testPointsDescriptionLabel");

        toolsLayout->addWidget(testPointsDescriptionLabel);

        toolsSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        toolsLayout->addItem(toolsSpacer);

        testPointsButton = new QPushButton(toolsGroupBox);
        testPointsButton->setObjectName("testPointsButton");

        toolsLayout->addWidget(testPointsButton);


        mainLayout->addWidget(toolsGroupBox);

        tcpServerGroupBox = new QGroupBox(centralwidget);
        tcpServerGroupBox->setObjectName("tcpServerGroupBox");
        tcpServerLayout = new QHBoxLayout(tcpServerGroupBox);
        tcpServerLayout->setObjectName("tcpServerLayout");
        tcpServerStatusLabel = new QLabel(tcpServerGroupBox);
        tcpServerStatusLabel->setObjectName("tcpServerStatusLabel");

        tcpServerLayout->addWidget(tcpServerStatusLabel);

        tcpServerSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        tcpServerLayout->addItem(tcpServerSpacer);

        startTcpServerButton = new QPushButton(tcpServerGroupBox);
        startTcpServerButton->setObjectName("startTcpServerButton");

        tcpServerLayout->addWidget(startTcpServerButton);

        stopTcpServerButton = new QPushButton(tcpServerGroupBox);
        stopTcpServerButton->setObjectName("stopTcpServerButton");
        stopTcpServerButton->setEnabled(false);

        tcpServerLayout->addWidget(stopTcpServerButton);


        mainLayout->addWidget(tcpServerGroupBox);

        logGroupBox = new QGroupBox(centralwidget);
        logGroupBox->setObjectName("logGroupBox");
        logLayout = new QVBoxLayout(logGroupBox);
        logLayout->setObjectName("logLayout");
        logEdit = new QPlainTextEdit(logGroupBox);
        logEdit->setObjectName("logEdit");
        logEdit->setMinimumSize(QSize(0, 120));
        logEdit->setReadOnly(true);

        logLayout->addWidget(logEdit);

        logButtonLayout = new QHBoxLayout();
        logButtonLayout->setObjectName("logButtonLayout");
        logSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        logButtonLayout->addItem(logSpacer);

        clearLogButton = new QPushButton(logGroupBox);
        clearLogButton->setObjectName("clearLogButton");

        logButtonLayout->addWidget(clearLogButton);


        logLayout->addLayout(logButtonLayout);


        mainLayout->addWidget(logGroupBox);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PC-DMIS \346\277\200\345\205\211\350\267\237\350\270\252\344\273\252\345\235\220\346\240\207\350\257\273\345\217\226\346\265\213\350\257\225", nullptr));
        connectionGroupBox->setTitle(QCoreApplication::translate("MainWindow", "1. PC-DMIS \350\277\236\346\216\245", nullptr));
        progIdTitleLabel->setText(QCoreApplication::translate("MainWindow", "COM ProgID\357\274\232", nullptr));
        progIdEdit->setText(QCoreApplication::translate("MainWindow", "PCDLRN.Application", nullptr));
        visibleCheckBox->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272 PC-DMIS", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245 PC-DMIS", nullptr));
        disconnectButton->setText(QCoreApplication::translate("MainWindow", "\346\226\255\345\274\200", nullptr));
        automationTitleLabel->setText(QCoreApplication::translate("MainWindow", "\350\275\257\344\273\266\346\216\245\345\217\243\357\274\232", nullptr));
        automationStatusLabel->setText(QCoreApplication::translate("MainWindow", "Automation \346\234\252\350\277\236\346\216\245", nullptr));
        readGroupBox->setTitle(QCoreApplication::translate("MainWindow", "2. \345\235\220\346\240\207\350\257\273\345\217\226", nullptr));
        coordinateModeTitleLabel->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\345\235\220\346\240\207\347\263\273\357\274\232", nullptr));
        coordinateModeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\344\273\252\345\231\250\345\235\220\346\240\207", nullptr));
        coordinateModeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215PC-DMIS\345\257\271\351\275\220\345\235\220\346\240\207", nullptr));

        intervalTitleLabel->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\351\227\264\351\232\224\357\274\232", nullptr));
        intervalSpinBox->setSuffix(QCoreApplication::translate("MainWindow", " ms", nullptr));
        readOnceButton->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\344\270\200\346\254\241", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\350\277\236\347\273\255\350\257\273\345\217\226", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\350\257\273\345\217\226", nullptr));
        xTitleLabel->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        yTitleLabel->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        zTitleLabel->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        xValueLabel->setText(QCoreApplication::translate("MainWindow", "0.000000", nullptr));
        yValueLabel->setText(QCoreApplication::translate("MainWindow", "0.000000", nullptr));
        zValueLabel->setText(QCoreApplication::translate("MainWindow", "0.000000", nullptr));
        coordinateSystemLabel->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\346\225\260\346\215\256\346\272\220\357\274\232Machine.ProbePosition\357\274\210\344\273\252\345\231\250\345\235\220\346\240\207\347\263\273\357\274\233\345\215\225\344\275\215\347\224\261 PC-DMIS \345\275\223\345\211\215\350\256\276\347\275\256\345\206\263\345\256\232\357\274\211", nullptr));
        sampleTimeTitleLabel->setText(QCoreApplication::translate("MainWindow", "\346\234\200\345\220\216\346\233\264\346\226\260\346\227\266\351\227\264\357\274\232", nullptr));
        sampleTimeLabel->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
        circleFitGroupBox->setTitle(QCoreApplication::translate("MainWindow", "3. \345\234\206\345\277\203\344\270\216\346\263\225\345\220\221\350\256\241\347\256\227", nullptr));
        circlePointCountLabel->setText(QCoreApplication::translate("MainWindow", "\345\267\262\351\207\207\351\233\206\357\274\2320 \347\202\271\357\274\210\350\207\263\345\260\221 3 \347\202\271\357\274\214\345\273\272\350\256\256 6 \347\202\271\344\273\245\344\270\212\357\274\211", nullptr));
        captureCirclePointButton->setText(QCoreApplication::translate("MainWindow", "\351\207\207\351\233\206\345\275\223\345\211\215\347\202\271", nullptr));
        deleteCirclePointButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\351\200\211\344\270\255\347\202\271", nullptr));
        clearCirclePointsButton->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        calculateCircleButton->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\345\234\206\345\277\203\344\270\216\345\247\277\346\200\201", nullptr));
        circlePointsTitleLabel->setText(QCoreApplication::translate("MainWindow", "\345\234\206\345\221\250\351\207\207\351\233\206\347\202\271\357\274\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem = circlePointsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = circlePointsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = circlePointsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = circlePointsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        circleResultDescriptionLabel->setText(QCoreApplication::translate("MainWindow", "\347\273\223\346\236\234\357\274\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = circleResultTable->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = circleResultTable->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = circleResultTable->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = circleResultTable->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = circleResultTable->horizontalHeaderItem(4);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = circleResultTable->horizontalHeaderItem(5);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = circleResultTable->horizontalHeaderItem(6);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "\345\215\212\345\276\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = circleResultTable->horizontalHeaderItem(7);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "\345\271\263\351\235\242RMS", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = circleResultTable->horizontalHeaderItem(8);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "\345\234\206RMS", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = circleResultTable->horizontalHeaderItem(9);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "\345\234\206\346\234\200\345\244\247\346\256\213\345\267\256", nullptr));
        toolsGroupBox->setTitle(QCoreApplication::translate("MainWindow", "4. \346\240\207\345\256\232\345\267\245\345\205\267", nullptr));
        testPointsDescriptionLabel->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\345\205\263\350\212\202\347\251\272\351\227\264\346\265\213\350\257\225\347\202\271\357\274\214\345\271\266\345\217\257\344\275\277\347\224\250 STL \345\217\257\350\276\276\345\237\237\350\277\233\350\241\214\350\277\207\346\273\244\357\274\232", nullptr));
        testPointsButton->setText(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225\347\202\271\347\224\237\346\210\220", nullptr));
        tcpServerGroupBox->setTitle(QCoreApplication::translate("MainWindow", "5. TCP\346\234\215\345\212\241\345\231\250", nullptr));
        tcpServerStatusLabel->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\346\234\252\345\220\257\345\212\250", nullptr));
        startTcpServerButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257\346\234\215\345\212\241\345\231\250", nullptr));
        stopTcpServerButton->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\346\234\215\345\212\241\345\231\250", nullptr));
        logGroupBox->setTitle(QCoreApplication::translate("MainWindow", "6. \350\277\220\350\241\214\346\227\245\345\277\227", nullptr));
        clearLogButton->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
