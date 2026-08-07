/********************************************************************************
** Form generated from reading UI file 'testpoints.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTPOINTS_H
#define UI_TESTPOINTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKOpenGLNativeWidget.h"

QT_BEGIN_NAMESPACE

class Ui_TestPoints
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *contentLayout;
    QGroupBox *jointGroupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_9;
    QLabel *label_min;
    QLabel *label_max;
    QLabel *label_J1;
    QLineEdit *lineEdit_J1_min;
    QLineEdit *lineEdit_J1_max;
    QLabel *label_J2;
    QLineEdit *lineEdit_J2_min;
    QLineEdit *lineEdit_J2_max;
    QLabel *label_J3;
    QLineEdit *lineEdit_J3_min;
    QLineEdit *lineEdit_J3_max;
    QLabel *label_J4;
    QLineEdit *lineEdit_J4_min;
    QLineEdit *lineEdit_J4_max;
    QLabel *label__J5;
    QLineEdit *lineEdit_J5_min;
    QLineEdit *lineEdit_J5_max;
    QLabel *label_J6;
    QLineEdit *lineEdit_J6_min;
    QLineEdit *lineEdit_J6_max;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QCheckBox *checkBox_Decimal;
    QGroupBox *trackerVisibilityGroupBox;
    QVBoxLayout *trackerVisibilityLayout;
    QCheckBox *trackerVisibilityCheckBox;
    QHBoxLayout *trackerConnectionLayout;
    QPushButton *refreshTrackerButton;
    QPushButton *testTrackerPositionButton;
    QLabel *trackerStatusLabel;
    QLabel *trackerPositionLabel;
    QGridLayout *trackerParameterLayout;
    QLabel *reflectorOffsetTitleLabel;
    QHBoxLayout *reflectorOffsetLayout;
    QDoubleSpinBox *reflectorOffsetXSpinBox;
    QDoubleSpinBox *reflectorOffsetYSpinBox;
    QDoubleSpinBox *reflectorOffsetZSpinBox;
    QLabel *reflectorAxisTitleLabel;
    QComboBox *reflectorAxisComboBox;
    QLabel *incidenceAngleTitleLabel;
    QDoubleSpinBox *incidenceAngleSpinBox;
    QLabel *rotationStepTitleLabel;
    QSpinBox *rotationStepSpinBox;
    QLabel *trackerRangeInfoLabel;
    QHBoxLayout *trackerActionLayout;
    QCheckBox *showTrackerRangeCheckBox;
    QSpacerItem *trackerActionSpacer;
    QSpacerItem *verticalSpacer;
    QGroupBox *stlGroupBox;
    QVBoxLayout *stlLayout;
    QHBoxLayout *stlToolbarLayout;
    QPushButton *loadStlButton;
    QPushButton *resetViewButton;
    QLabel *stlPathLabel;
    QVTKOpenGLNativeWidget *stlView;
    QGroupBox *regionGroupBox;
    QGridLayout *regionLayout;
    QLabel *regionSizeTitleLabel;
    QSlider *regionSizeSlider;
    QLabel *regionSizeValueLabel;
    QLabel *regionXTitleLabel;
    QSlider *regionXSlider;
    QLabel *regionXValueLabel;
    QLabel *regionYTitleLabel;
    QSlider *regionYSlider;
    QLabel *regionYValueLabel;
    QLabel *regionZTitleLabel;
    QSlider *regionZSlider;
    QLabel *regionZValueLabel;
    QCheckBox *checkBox_filter;
    QLabel *regionBoundsLabel;
    QPushButton *resetRegionButton;
    QGroupBox *generationGroupBox;
    QVBoxLayout *generationLayout;
    QHBoxLayout *generationActionsLayout;
    QLabel *label_count;
    QLineEdit *lineEdit_count;
    QLabel *label;
    QLabel *label_expected_count;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *previewTrackerButton;
    QPushButton *exportPreviewPoseButton;
    QPushButton *pushButton_Confirm;
    QLabel *trackerResultLabel;

    void setupUi(QDialog *TestPoints)
    {
        if (TestPoints->objectName().isEmpty())
            TestPoints->setObjectName("TestPoints");
        TestPoints->resize(971, 720);
        TestPoints->setMinimumSize(QSize(920, 720));
        verticalLayout_2 = new QVBoxLayout(TestPoints);
        verticalLayout_2->setSpacing(12);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(16, 16, 16, 16);
        contentLayout = new QHBoxLayout();
        contentLayout->setSpacing(12);
        contentLayout->setObjectName("contentLayout");
        jointGroupBox = new QGroupBox(TestPoints);
        jointGroupBox->setObjectName("jointGroupBox");
        jointGroupBox->setMinimumSize(QSize(340, 0));
        jointGroupBox->setMaximumSize(QSize(380, 16777215));
        verticalLayout = new QVBoxLayout(jointGroupBox);
        verticalLayout->setSpacing(14);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setHorizontalSpacing(12);
        gridLayout->setVerticalSpacing(10);
        label_9 = new QLabel(jointGroupBox);
        label_9->setObjectName("label_9");
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_9, 0, 0, 1, 1);

        label_min = new QLabel(jointGroupBox);
        label_min->setObjectName("label_min");
        label_min->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_min, 0, 1, 1, 1);

        label_max = new QLabel(jointGroupBox);
        label_max->setObjectName("label_max");
        label_max->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_max, 0, 2, 1, 1);

        label_J1 = new QLabel(jointGroupBox);
        label_J1->setObjectName("label_J1");
        label_J1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_J1, 1, 0, 1, 1);

        lineEdit_J1_min = new QLineEdit(jointGroupBox);
        lineEdit_J1_min->setObjectName("lineEdit_J1_min");
        lineEdit_J1_min->setMinimumSize(QSize(105, 30));
        lineEdit_J1_min->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J1_min, 1, 1, 1, 1);

        lineEdit_J1_max = new QLineEdit(jointGroupBox);
        lineEdit_J1_max->setObjectName("lineEdit_J1_max");
        lineEdit_J1_max->setMinimumSize(QSize(105, 30));
        lineEdit_J1_max->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J1_max, 1, 2, 1, 1);

        label_J2 = new QLabel(jointGroupBox);
        label_J2->setObjectName("label_J2");
        label_J2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_J2, 2, 0, 1, 1);

        lineEdit_J2_min = new QLineEdit(jointGroupBox);
        lineEdit_J2_min->setObjectName("lineEdit_J2_min");
        lineEdit_J2_min->setMinimumSize(QSize(105, 30));
        lineEdit_J2_min->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J2_min, 2, 1, 1, 1);

        lineEdit_J2_max = new QLineEdit(jointGroupBox);
        lineEdit_J2_max->setObjectName("lineEdit_J2_max");
        lineEdit_J2_max->setMinimumSize(QSize(105, 30));
        lineEdit_J2_max->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J2_max, 2, 2, 1, 1);

        label_J3 = new QLabel(jointGroupBox);
        label_J3->setObjectName("label_J3");
        label_J3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_J3, 3, 0, 1, 1);

        lineEdit_J3_min = new QLineEdit(jointGroupBox);
        lineEdit_J3_min->setObjectName("lineEdit_J3_min");
        lineEdit_J3_min->setMinimumSize(QSize(105, 30));
        lineEdit_J3_min->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J3_min, 3, 1, 1, 1);

        lineEdit_J3_max = new QLineEdit(jointGroupBox);
        lineEdit_J3_max->setObjectName("lineEdit_J3_max");
        lineEdit_J3_max->setMinimumSize(QSize(105, 30));
        lineEdit_J3_max->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J3_max, 3, 2, 1, 1);

        label_J4 = new QLabel(jointGroupBox);
        label_J4->setObjectName("label_J4");
        label_J4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_J4, 4, 0, 1, 1);

        lineEdit_J4_min = new QLineEdit(jointGroupBox);
        lineEdit_J4_min->setObjectName("lineEdit_J4_min");
        lineEdit_J4_min->setMinimumSize(QSize(105, 30));
        lineEdit_J4_min->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J4_min, 4, 1, 1, 1);

        lineEdit_J4_max = new QLineEdit(jointGroupBox);
        lineEdit_J4_max->setObjectName("lineEdit_J4_max");
        lineEdit_J4_max->setMinimumSize(QSize(105, 30));
        lineEdit_J4_max->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J4_max, 4, 2, 1, 1);

        label__J5 = new QLabel(jointGroupBox);
        label__J5->setObjectName("label__J5");
        label__J5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label__J5, 5, 0, 1, 1);

        lineEdit_J5_min = new QLineEdit(jointGroupBox);
        lineEdit_J5_min->setObjectName("lineEdit_J5_min");
        lineEdit_J5_min->setMinimumSize(QSize(105, 30));
        lineEdit_J5_min->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J5_min, 5, 1, 1, 1);

        lineEdit_J5_max = new QLineEdit(jointGroupBox);
        lineEdit_J5_max->setObjectName("lineEdit_J5_max");
        lineEdit_J5_max->setMinimumSize(QSize(105, 30));
        lineEdit_J5_max->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J5_max, 5, 2, 1, 1);

        label_J6 = new QLabel(jointGroupBox);
        label_J6->setObjectName("label_J6");
        label_J6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_J6, 6, 0, 1, 1);

        lineEdit_J6_min = new QLineEdit(jointGroupBox);
        lineEdit_J6_min->setObjectName("lineEdit_J6_min");
        lineEdit_J6_min->setMinimumSize(QSize(105, 30));
        lineEdit_J6_min->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J6_min, 6, 1, 1, 1);

        lineEdit_J6_max = new QLineEdit(jointGroupBox);
        lineEdit_J6_max->setObjectName("lineEdit_J6_max");
        lineEdit_J6_max->setMinimumSize(QSize(105, 30));
        lineEdit_J6_max->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_J6_max, 6, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        widget = new QWidget(jointGroupBox);
        widget->setObjectName("widget");
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        checkBox_Decimal = new QCheckBox(widget);
        checkBox_Decimal->setObjectName("checkBox_Decimal");

        gridLayout_3->addWidget(checkBox_Decimal, 0, 0, 1, 1);


        verticalLayout->addWidget(widget);

        trackerVisibilityGroupBox = new QGroupBox(jointGroupBox);
        trackerVisibilityGroupBox->setObjectName("trackerVisibilityGroupBox");
        trackerVisibilityLayout = new QVBoxLayout(trackerVisibilityGroupBox);
        trackerVisibilityLayout->setSpacing(8);
        trackerVisibilityLayout->setObjectName("trackerVisibilityLayout");
        trackerVisibilityLayout->setContentsMargins(10, 10, 10, 10);
        trackerVisibilityCheckBox = new QCheckBox(trackerVisibilityGroupBox);
        trackerVisibilityCheckBox->setObjectName("trackerVisibilityCheckBox");

        trackerVisibilityLayout->addWidget(trackerVisibilityCheckBox);

        trackerConnectionLayout = new QHBoxLayout();
        trackerConnectionLayout->setObjectName("trackerConnectionLayout");
        refreshTrackerButton = new QPushButton(trackerVisibilityGroupBox);
        refreshTrackerButton->setObjectName("refreshTrackerButton");
        refreshTrackerButton->setMinimumSize(QSize(118, 30));

        trackerConnectionLayout->addWidget(refreshTrackerButton);

        testTrackerPositionButton = new QPushButton(trackerVisibilityGroupBox);
        testTrackerPositionButton->setObjectName("testTrackerPositionButton");
        testTrackerPositionButton->setMinimumSize(QSize(105, 30));

        trackerConnectionLayout->addWidget(testTrackerPositionButton);

        trackerStatusLabel = new QLabel(trackerVisibilityGroupBox);
        trackerStatusLabel->setObjectName("trackerStatusLabel");
        trackerStatusLabel->setWordWrap(true);

        trackerConnectionLayout->addWidget(trackerStatusLabel);


        trackerVisibilityLayout->addLayout(trackerConnectionLayout);

        trackerPositionLabel = new QLabel(trackerVisibilityGroupBox);
        trackerPositionLabel->setObjectName("trackerPositionLabel");
        trackerPositionLabel->setStyleSheet(QString::fromUtf8("color: #4b5563;"));

        trackerVisibilityLayout->addWidget(trackerPositionLabel);

        trackerParameterLayout = new QGridLayout();
        trackerParameterLayout->setObjectName("trackerParameterLayout");
        trackerParameterLayout->setHorizontalSpacing(8);
        trackerParameterLayout->setVerticalSpacing(6);
        reflectorOffsetTitleLabel = new QLabel(trackerVisibilityGroupBox);
        reflectorOffsetTitleLabel->setObjectName("reflectorOffsetTitleLabel");

        trackerParameterLayout->addWidget(reflectorOffsetTitleLabel, 0, 0, 1, 1);

        reflectorOffsetLayout = new QHBoxLayout();
        reflectorOffsetLayout->setSpacing(3);
        reflectorOffsetLayout->setObjectName("reflectorOffsetLayout");
        reflectorOffsetXSpinBox = new QDoubleSpinBox(trackerVisibilityGroupBox);
        reflectorOffsetXSpinBox->setObjectName("reflectorOffsetXSpinBox");
        reflectorOffsetXSpinBox->setDecimals(1);
        reflectorOffsetXSpinBox->setMinimum(-10000.000000000000000);
        reflectorOffsetXSpinBox->setMaximum(10000.000000000000000);
        reflectorOffsetXSpinBox->setSingleStep(1.000000000000000);

        reflectorOffsetLayout->addWidget(reflectorOffsetXSpinBox);

        reflectorOffsetYSpinBox = new QDoubleSpinBox(trackerVisibilityGroupBox);
        reflectorOffsetYSpinBox->setObjectName("reflectorOffsetYSpinBox");
        reflectorOffsetYSpinBox->setDecimals(1);
        reflectorOffsetYSpinBox->setMinimum(-10000.000000000000000);
        reflectorOffsetYSpinBox->setMaximum(10000.000000000000000);
        reflectorOffsetYSpinBox->setSingleStep(1.000000000000000);

        reflectorOffsetLayout->addWidget(reflectorOffsetYSpinBox);

        reflectorOffsetZSpinBox = new QDoubleSpinBox(trackerVisibilityGroupBox);
        reflectorOffsetZSpinBox->setObjectName("reflectorOffsetZSpinBox");
        reflectorOffsetZSpinBox->setDecimals(1);
        reflectorOffsetZSpinBox->setMinimum(-10000.000000000000000);
        reflectorOffsetZSpinBox->setMaximum(10000.000000000000000);
        reflectorOffsetZSpinBox->setSingleStep(1.000000000000000);

        reflectorOffsetLayout->addWidget(reflectorOffsetZSpinBox);


        trackerParameterLayout->addLayout(reflectorOffsetLayout, 0, 1, 1, 1);

        reflectorAxisTitleLabel = new QLabel(trackerVisibilityGroupBox);
        reflectorAxisTitleLabel->setObjectName("reflectorAxisTitleLabel");

        trackerParameterLayout->addWidget(reflectorAxisTitleLabel, 1, 0, 1, 1);

        reflectorAxisComboBox = new QComboBox(trackerVisibilityGroupBox);
        reflectorAxisComboBox->addItem(QString());
        reflectorAxisComboBox->addItem(QString());
        reflectorAxisComboBox->addItem(QString());
        reflectorAxisComboBox->addItem(QString());
        reflectorAxisComboBox->addItem(QString());
        reflectorAxisComboBox->addItem(QString());
        reflectorAxisComboBox->addItem(QString());
        reflectorAxisComboBox->addItem(QString());
        reflectorAxisComboBox->setObjectName("reflectorAxisComboBox");

        trackerParameterLayout->addWidget(reflectorAxisComboBox, 1, 1, 1, 1);

        incidenceAngleTitleLabel = new QLabel(trackerVisibilityGroupBox);
        incidenceAngleTitleLabel->setObjectName("incidenceAngleTitleLabel");

        trackerParameterLayout->addWidget(incidenceAngleTitleLabel, 2, 0, 1, 1);

        incidenceAngleSpinBox = new QDoubleSpinBox(trackerVisibilityGroupBox);
        incidenceAngleSpinBox->setObjectName("incidenceAngleSpinBox");
        incidenceAngleSpinBox->setDecimals(1);
        incidenceAngleSpinBox->setMinimum(1.000000000000000);
        incidenceAngleSpinBox->setMaximum(89.000000000000000);
        incidenceAngleSpinBox->setSingleStep(1.000000000000000);
        incidenceAngleSpinBox->setValue(45.000000000000000);

        trackerParameterLayout->addWidget(incidenceAngleSpinBox, 2, 1, 1, 1);

        rotationStepTitleLabel = new QLabel(trackerVisibilityGroupBox);
        rotationStepTitleLabel->setObjectName("rotationStepTitleLabel");

        trackerParameterLayout->addWidget(rotationStepTitleLabel, 3, 0, 1, 1);

        rotationStepSpinBox = new QSpinBox(trackerVisibilityGroupBox);
        rotationStepSpinBox->setObjectName("rotationStepSpinBox");
        rotationStepSpinBox->setMinimum(1);
        rotationStepSpinBox->setMaximum(45);
        rotationStepSpinBox->setValue(5);

        trackerParameterLayout->addWidget(rotationStepSpinBox, 3, 1, 1, 1);


        trackerVisibilityLayout->addLayout(trackerParameterLayout);

        trackerRangeInfoLabel = new QLabel(trackerVisibilityGroupBox);
        trackerRangeInfoLabel->setObjectName("trackerRangeInfoLabel");
        trackerRangeInfoLabel->setStyleSheet(QString::fromUtf8("color: #6b7280;"));
        trackerRangeInfoLabel->setWordWrap(true);

        trackerVisibilityLayout->addWidget(trackerRangeInfoLabel);

        trackerActionLayout = new QHBoxLayout();
        trackerActionLayout->setObjectName("trackerActionLayout");
        showTrackerRangeCheckBox = new QCheckBox(trackerVisibilityGroupBox);
        showTrackerRangeCheckBox->setObjectName("showTrackerRangeCheckBox");
        showTrackerRangeCheckBox->setChecked(true);

        trackerActionLayout->addWidget(showTrackerRangeCheckBox);

        trackerActionSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        trackerActionLayout->addItem(trackerActionSpacer);


        trackerVisibilityLayout->addLayout(trackerActionLayout);


        verticalLayout->addWidget(trackerVisibilityGroupBox);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(2, 4);

        contentLayout->addWidget(jointGroupBox);

        stlGroupBox = new QGroupBox(TestPoints);
        stlGroupBox->setObjectName("stlGroupBox");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(stlGroupBox->sizePolicy().hasHeightForWidth());
        stlGroupBox->setSizePolicy(sizePolicy);
        stlLayout = new QVBoxLayout(stlGroupBox);
        stlLayout->setSpacing(10);
        stlLayout->setObjectName("stlLayout");
        stlToolbarLayout = new QHBoxLayout();
        stlToolbarLayout->setSpacing(8);
        stlToolbarLayout->setObjectName("stlToolbarLayout");
        loadStlButton = new QPushButton(stlGroupBox);
        loadStlButton->setObjectName("loadStlButton");
        loadStlButton->setMinimumSize(QSize(90, 30));

        stlToolbarLayout->addWidget(loadStlButton);

        resetViewButton = new QPushButton(stlGroupBox);
        resetViewButton->setObjectName("resetViewButton");
        resetViewButton->setMinimumSize(QSize(90, 30));

        stlToolbarLayout->addWidget(resetViewButton);

        stlPathLabel = new QLabel(stlGroupBox);
        stlPathLabel->setObjectName("stlPathLabel");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stlPathLabel->sizePolicy().hasHeightForWidth());
        stlPathLabel->setSizePolicy(sizePolicy1);
        stlPathLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        stlToolbarLayout->addWidget(stlPathLabel);


        stlLayout->addLayout(stlToolbarLayout);

        stlView = new QVTKOpenGLNativeWidget(stlGroupBox);
        stlView->setObjectName("stlView");
        sizePolicy.setHeightForWidth(stlView->sizePolicy().hasHeightForWidth());
        stlView->setSizePolicy(sizePolicy);
        stlView->setMinimumSize(QSize(520, 200));

        stlLayout->addWidget(stlView);

        regionGroupBox = new QGroupBox(stlGroupBox);
        regionGroupBox->setObjectName("regionGroupBox");
        regionGroupBox->setEnabled(false);
        regionLayout = new QGridLayout(regionGroupBox);
        regionLayout->setObjectName("regionLayout");
        regionLayout->setHorizontalSpacing(8);
        regionLayout->setVerticalSpacing(6);
        regionSizeTitleLabel = new QLabel(regionGroupBox);
        regionSizeTitleLabel->setObjectName("regionSizeTitleLabel");

        regionLayout->addWidget(regionSizeTitleLabel, 0, 0, 1, 1);

        regionSizeSlider = new QSlider(regionGroupBox);
        regionSizeSlider->setObjectName("regionSizeSlider");
        regionSizeSlider->setMinimum(0);
        regionSizeSlider->setMaximum(100);
        regionSizeSlider->setValue(40);
        regionSizeSlider->setOrientation(Qt::Horizontal);

        regionLayout->addWidget(regionSizeSlider, 0, 1, 1, 1);

        regionSizeValueLabel = new QLabel(regionGroupBox);
        regionSizeValueLabel->setObjectName("regionSizeValueLabel");
        regionSizeValueLabel->setMinimumSize(QSize(42, 0));
        regionSizeValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        regionLayout->addWidget(regionSizeValueLabel, 0, 2, 1, 1);

        regionXTitleLabel = new QLabel(regionGroupBox);
        regionXTitleLabel->setObjectName("regionXTitleLabel");

        regionLayout->addWidget(regionXTitleLabel, 1, 0, 1, 1);

        regionXSlider = new QSlider(regionGroupBox);
        regionXSlider->setObjectName("regionXSlider");
        regionXSlider->setMaximum(1000);
        regionXSlider->setValue(500);
        regionXSlider->setOrientation(Qt::Horizontal);

        regionLayout->addWidget(regionXSlider, 1, 1, 1, 1);

        regionXValueLabel = new QLabel(regionGroupBox);
        regionXValueLabel->setObjectName("regionXValueLabel");
        regionXValueLabel->setMinimumSize(QSize(72, 0));
        regionXValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        regionLayout->addWidget(regionXValueLabel, 1, 2, 1, 1);

        regionYTitleLabel = new QLabel(regionGroupBox);
        regionYTitleLabel->setObjectName("regionYTitleLabel");

        regionLayout->addWidget(regionYTitleLabel, 2, 0, 1, 1);

        regionYSlider = new QSlider(regionGroupBox);
        regionYSlider->setObjectName("regionYSlider");
        regionYSlider->setMaximum(1000);
        regionYSlider->setValue(500);
        regionYSlider->setOrientation(Qt::Horizontal);

        regionLayout->addWidget(regionYSlider, 2, 1, 1, 1);

        regionYValueLabel = new QLabel(regionGroupBox);
        regionYValueLabel->setObjectName("regionYValueLabel");
        regionYValueLabel->setMinimumSize(QSize(72, 0));
        regionYValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        regionLayout->addWidget(regionYValueLabel, 2, 2, 1, 1);

        regionZTitleLabel = new QLabel(regionGroupBox);
        regionZTitleLabel->setObjectName("regionZTitleLabel");

        regionLayout->addWidget(regionZTitleLabel, 3, 0, 1, 1);

        regionZSlider = new QSlider(regionGroupBox);
        regionZSlider->setObjectName("regionZSlider");
        regionZSlider->setMaximum(1000);
        regionZSlider->setValue(500);
        regionZSlider->setOrientation(Qt::Horizontal);

        regionLayout->addWidget(regionZSlider, 3, 1, 1, 1);

        regionZValueLabel = new QLabel(regionGroupBox);
        regionZValueLabel->setObjectName("regionZValueLabel");
        regionZValueLabel->setMinimumSize(QSize(72, 0));
        regionZValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        regionLayout->addWidget(regionZValueLabel, 3, 2, 1, 1);

        checkBox_filter = new QCheckBox(regionGroupBox);
        checkBox_filter->setObjectName("checkBox_filter");

        regionLayout->addWidget(checkBox_filter, 4, 0, 1, 1);

        regionBoundsLabel = new QLabel(regionGroupBox);
        regionBoundsLabel->setObjectName("regionBoundsLabel");

        regionLayout->addWidget(regionBoundsLabel, 4, 1, 1, 1);

        resetRegionButton = new QPushButton(regionGroupBox);
        resetRegionButton->setObjectName("resetRegionButton");
        resetRegionButton->setMinimumSize(QSize(104, 28));

        regionLayout->addWidget(resetRegionButton, 4, 2, 1, 1);


        stlLayout->addWidget(regionGroupBox);


        contentLayout->addWidget(stlGroupBox);


        verticalLayout_2->addLayout(contentLayout);

        generationGroupBox = new QGroupBox(TestPoints);
        generationGroupBox->setObjectName("generationGroupBox");
        generationLayout = new QVBoxLayout(generationGroupBox);
        generationLayout->setSpacing(8);
        generationLayout->setObjectName("generationLayout");
        generationActionsLayout = new QHBoxLayout();
        generationActionsLayout->setSpacing(10);
        generationActionsLayout->setObjectName("generationActionsLayout");
        label_count = new QLabel(generationGroupBox);
        label_count->setObjectName("label_count");

        generationActionsLayout->addWidget(label_count);

        lineEdit_count = new QLineEdit(generationGroupBox);
        lineEdit_count->setObjectName("lineEdit_count");
        lineEdit_count->setMinimumSize(QSize(180, 32));
        lineEdit_count->setMaximumSize(QSize(260, 16777215));

        generationActionsLayout->addWidget(lineEdit_count);

        label = new QLabel(generationGroupBox);
        label->setObjectName("label");

        generationActionsLayout->addWidget(label);

        label_expected_count = new QLabel(generationGroupBox);
        label_expected_count->setObjectName("label_expected_count");
        label_expected_count->setMinimumSize(QSize(70, 0));
        QFont font;
        font.setBold(true);
        label_expected_count->setFont(font);

        generationActionsLayout->addWidget(label_expected_count);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        generationActionsLayout->addItem(horizontalSpacer_2);

        previewTrackerButton = new QPushButton(generationGroupBox);
        previewTrackerButton->setObjectName("previewTrackerButton");
        previewTrackerButton->setMinimumSize(QSize(112, 36));

        generationActionsLayout->addWidget(previewTrackerButton);

        exportPreviewPoseButton = new QPushButton(generationGroupBox);
        exportPreviewPoseButton->setObjectName("exportPreviewPoseButton");
        exportPreviewPoseButton->setEnabled(false);
        exportPreviewPoseButton->setMinimumSize(QSize(112, 36));

        generationActionsLayout->addWidget(exportPreviewPoseButton);

        pushButton_Confirm = new QPushButton(generationGroupBox);
        pushButton_Confirm->setObjectName("pushButton_Confirm");
        pushButton_Confirm->setMinimumSize(QSize(120, 36));

        generationActionsLayout->addWidget(pushButton_Confirm);


        generationLayout->addLayout(generationActionsLayout);

        trackerResultLabel = new QLabel(generationGroupBox);
        trackerResultLabel->setObjectName("trackerResultLabel");
        trackerResultLabel->setMinimumSize(QSize(0, 54));
        trackerResultLabel->setStyleSheet(QString::fromUtf8("QLabel { color: #374151; background: #f7f8fa; border: 1px solid #d9dde3; border-radius: 3px; padding: 6px 8px; }"));
        trackerResultLabel->setWordWrap(true);

        generationLayout->addWidget(trackerResultLabel);


        verticalLayout_2->addWidget(generationGroupBox);

        QWidget::setTabOrder(lineEdit_J1_min, lineEdit_J1_max);
        QWidget::setTabOrder(lineEdit_J1_max, lineEdit_J2_min);
        QWidget::setTabOrder(lineEdit_J2_min, lineEdit_J2_max);
        QWidget::setTabOrder(lineEdit_J2_max, lineEdit_J3_min);
        QWidget::setTabOrder(lineEdit_J3_min, lineEdit_J3_max);
        QWidget::setTabOrder(lineEdit_J3_max, lineEdit_J4_min);
        QWidget::setTabOrder(lineEdit_J4_min, lineEdit_J4_max);
        QWidget::setTabOrder(lineEdit_J4_max, lineEdit_J5_min);
        QWidget::setTabOrder(lineEdit_J5_min, lineEdit_J5_max);
        QWidget::setTabOrder(lineEdit_J5_max, lineEdit_J6_min);
        QWidget::setTabOrder(lineEdit_J6_min, lineEdit_J6_max);
        QWidget::setTabOrder(lineEdit_J6_max, checkBox_Decimal);
        QWidget::setTabOrder(checkBox_Decimal, loadStlButton);
        QWidget::setTabOrder(loadStlButton, resetViewButton);
        QWidget::setTabOrder(resetViewButton, regionSizeSlider);
        QWidget::setTabOrder(regionSizeSlider, regionXSlider);
        QWidget::setTabOrder(regionXSlider, regionYSlider);
        QWidget::setTabOrder(regionYSlider, regionZSlider);
        QWidget::setTabOrder(regionZSlider, checkBox_filter);
        QWidget::setTabOrder(checkBox_filter, resetRegionButton);
        QWidget::setTabOrder(resetRegionButton, lineEdit_count);
        QWidget::setTabOrder(lineEdit_count, pushButton_Confirm);

        retranslateUi(TestPoints);

        QMetaObject::connectSlotsByName(TestPoints);
    } // setupUi

    void retranslateUi(QDialog *TestPoints)
    {
        TestPoints->setWindowTitle(QCoreApplication::translate("TestPoints", "\346\265\213\350\257\225\347\202\271\347\224\237\346\210\220", nullptr));
        jointGroupBox->setTitle(QCoreApplication::translate("TestPoints", "\345\205\263\350\212\202\350\214\203\345\233\264", nullptr));
        label_9->setText(QCoreApplication::translate("TestPoints", "\345\205\263\350\212\202", nullptr));
        label_min->setText(QCoreApplication::translate("TestPoints", "\346\234\200\345\260\217\345\200\274", nullptr));
        label_max->setText(QCoreApplication::translate("TestPoints", "\346\234\200\345\244\247\345\200\274", nullptr));
        label_J1->setText(QCoreApplication::translate("TestPoints", "J1", nullptr));
        lineEdit_J1_min->setText(QCoreApplication::translate("TestPoints", "0", nullptr));
        lineEdit_J1_max->setText(QCoreApplication::translate("TestPoints", "300", nullptr));
        label_J2->setText(QCoreApplication::translate("TestPoints", "J2", nullptr));
        lineEdit_J2_min->setText(QCoreApplication::translate("TestPoints", "0", nullptr));
        lineEdit_J2_max->setText(QCoreApplication::translate("TestPoints", "300", nullptr));
        label_J3->setText(QCoreApplication::translate("TestPoints", "J3", nullptr));
        lineEdit_J3_min->setText(QCoreApplication::translate("TestPoints", "0", nullptr));
        lineEdit_J3_max->setText(QCoreApplication::translate("TestPoints", "300", nullptr));
        label_J4->setText(QCoreApplication::translate("TestPoints", "J4", nullptr));
        lineEdit_J4_min->setText(QCoreApplication::translate("TestPoints", "-180", nullptr));
        lineEdit_J4_max->setText(QCoreApplication::translate("TestPoints", "180", nullptr));
        label__J5->setText(QCoreApplication::translate("TestPoints", "J5", nullptr));
        lineEdit_J5_min->setText(QCoreApplication::translate("TestPoints", "15", nullptr));
        lineEdit_J5_max->setText(QCoreApplication::translate("TestPoints", "135", nullptr));
#if QT_CONFIG(tooltip)
        label_J6->setToolTip(QCoreApplication::translate("TestPoints", "\347\213\254\347\253\213\344\270\273\350\275\264\357\274\214\344\270\215\345\217\202\344\270\216J1\357\275\236J5\346\265\213\350\257\225\344\275\215\345\247\277\347\273\204\345\220\210\357\274\233\345\217\257\350\247\201\346\200\247\347\255\233\351\200\211\344\274\232\346\250\241\346\213\237\346\227\213\350\275\254\344\270\200\345\221\250\343\200\202", nullptr));
#endif // QT_CONFIG(tooltip)
        label_J6->setText(QCoreApplication::translate("TestPoints", "J6\344\270\273\350\275\264", nullptr));
        lineEdit_J6_min->setText(QCoreApplication::translate("TestPoints", "0", nullptr));
        lineEdit_J6_max->setText(QCoreApplication::translate("TestPoints", "0", nullptr));
        checkBox_Decimal->setText(QCoreApplication::translate("TestPoints", "\347\224\237\346\210\220\345\260\217\346\225\260\357\274\210\346\255\245\351\225\277 0.5\357\274\211", nullptr));
        trackerVisibilityGroupBox->setTitle(QCoreApplication::translate("TestPoints", "\346\277\200\345\205\211\350\267\237\350\270\252\344\273\252\345\217\257\350\247\201\346\200\247\347\255\233\351\200\211", nullptr));
#if QT_CONFIG(tooltip)
        trackerVisibilityCheckBox->setToolTip(QCoreApplication::translate("TestPoints", "J1\357\275\236J5\344\277\235\346\214\201\345\275\223\345\211\215\346\255\243\350\247\243\344\275\215\345\247\277\357\274\214\346\250\241\346\213\237\347\213\254\347\253\213\344\270\273\350\275\264J6\346\227\213\350\275\254360\302\260\357\274\233\351\235\266\347\220\203\346\225\264\345\221\250\345\235\207\345\217\257\350\247\201\346\211\215\344\277\235\347\225\231\347\202\271\344\275\215\343\200\202", nullptr));
#endif // QT_CONFIG(tooltip)
        trackerVisibilityCheckBox->setText(QCoreApplication::translate("TestPoints", "\347\224\237\346\210\220\346\227\266\345\220\257\347\224\250 J6 \346\225\264\345\221\250\345\217\257\350\247\201\346\200\247\347\255\233\351\200\211", nullptr));
        refreshTrackerButton->setText(QCoreApplication::translate("TestPoints", "\350\216\267\345\217\226/\345\210\267\346\226\260\344\275\215\347\275\256", nullptr));
#if QT_CONFIG(tooltip)
        testTrackerPositionButton->setToolTip(QCoreApplication::translate("TestPoints", "\344\270\215\350\256\277\351\227\256PC-DMIS\357\274\214\345\247\213\347\273\210\344\275\277\347\224\250\345\233\272\345\256\232\346\265\213\350\257\225\344\275\215\347\275\256X=0\343\200\201Y=2000\343\200\201Z=-5000 mm\357\274\233\345\212\240\350\275\275STL\344\270\215\344\274\232\346\224\271\345\217\230\350\257\245\345\235\220\346\240\207\343\200\202", nullptr));
#endif // QT_CONFIG(tooltip)
        testTrackerPositionButton->setText(QCoreApplication::translate("TestPoints", "\344\275\277\347\224\250\346\265\213\350\257\225\344\275\215\347\275\256", nullptr));
        trackerStatusLabel->setText(QCoreApplication::translate("TestPoints", "\345\260\232\346\234\252\345\217\226\345\276\227\346\264\273\345\212\250\345\257\271\351\275\220\344\270\255\347\232\204\344\273\252\345\231\250\344\275\215\347\275\256", nullptr));
        trackerPositionLabel->setText(QCoreApplication::translate("TestPoints", "\344\275\215\347\275\256\357\274\232X --   Y --   Z --", nullptr));
#if QT_CONFIG(tooltip)
        reflectorOffsetTitleLabel->setToolTip(QCoreApplication::translate("TestPoints", "J6=0\302\260\346\227\266\357\274\214\351\235\266\347\220\203\344\270\255\345\277\203\345\234\250TCP\345\235\220\346\240\207\347\263\273\344\270\255\347\232\204\345\256\211\350\243\205\345\201\217\347\247\273\357\274\214\345\215\225\344\275\215mm\343\200\202", nullptr));
#endif // QT_CONFIG(tooltip)
        reflectorOffsetTitleLabel->setText(QCoreApplication::translate("TestPoints", "\351\235\266\347\220\203\347\233\270\345\257\271TCP", nullptr));
#if QT_CONFIG(tooltip)
        reflectorOffsetXSpinBox->setToolTip(QCoreApplication::translate("TestPoints", "\351\235\266\347\220\203\344\270\255\345\277\203\347\233\270\345\257\271TCP\347\232\204X\345\201\217\347\247\273\357\274\210mm\357\274\211", nullptr));
#endif // QT_CONFIG(tooltip)
        reflectorOffsetXSpinBox->setPrefix(QCoreApplication::translate("TestPoints", "X ", nullptr));
#if QT_CONFIG(tooltip)
        reflectorOffsetYSpinBox->setToolTip(QCoreApplication::translate("TestPoints", "\351\235\266\347\220\203\344\270\255\345\277\203\347\233\270\345\257\271TCP\347\232\204Y\345\201\217\347\247\273\357\274\210mm\357\274\211", nullptr));
#endif // QT_CONFIG(tooltip)
        reflectorOffsetYSpinBox->setPrefix(QCoreApplication::translate("TestPoints", "Y ", nullptr));
#if QT_CONFIG(tooltip)
        reflectorOffsetZSpinBox->setToolTip(QCoreApplication::translate("TestPoints", "\351\235\266\347\220\203\344\270\255\345\277\203\347\233\270\345\257\271TCP\347\232\204Z\345\201\217\347\247\273\357\274\210mm\357\274\211", nullptr));
#endif // QT_CONFIG(tooltip)
        reflectorOffsetZSpinBox->setPrefix(QCoreApplication::translate("TestPoints", "Z ", nullptr));
        reflectorAxisTitleLabel->setText(QCoreApplication::translate("TestPoints", "\351\235\266\347\220\203\345\274\200\345\217\243\346\226\271\345\220\221", nullptr));
        reflectorAxisComboBox->setItemText(0, QCoreApplication::translate("TestPoints", "\346\262\277 TCP \342\206\222 \351\235\266\347\220\203\357\274\210\345\276\204\345\220\221\357\274\211", nullptr));
        reflectorAxisComboBox->setItemText(1, QCoreApplication::translate("TestPoints", "\346\262\277 \351\235\266\347\220\203 \342\206\222 TCP\357\274\210\345\217\215\345\220\221\345\276\204\345\220\221\357\274\211", nullptr));
        reflectorAxisComboBox->setItemText(2, QCoreApplication::translate("TestPoints", "TCP +Z", nullptr));
        reflectorAxisComboBox->setItemText(3, QCoreApplication::translate("TestPoints", "TCP -Z", nullptr));
        reflectorAxisComboBox->setItemText(4, QCoreApplication::translate("TestPoints", "TCP +X", nullptr));
        reflectorAxisComboBox->setItemText(5, QCoreApplication::translate("TestPoints", "TCP -X", nullptr));
        reflectorAxisComboBox->setItemText(6, QCoreApplication::translate("TestPoints", "TCP +Y", nullptr));
        reflectorAxisComboBox->setItemText(7, QCoreApplication::translate("TestPoints", "TCP -Y", nullptr));

#if QT_CONFIG(tooltip)
        reflectorAxisComboBox->setToolTip(QCoreApplication::translate("TestPoints", "\351\200\211\346\213\251J6=0\302\260\346\227\266\351\235\266\347\220\203\345\274\200\345\217\243\346\263\225\345\220\221\343\200\202\345\274\200\345\217\243\346\263\225\345\220\221\344\274\232\344\270\216\351\235\266\347\220\203\345\201\217\347\247\273\344\270\200\350\265\267\347\273\225TCP +Z\350\275\264\346\227\213\350\275\254\343\200\202", nullptr));
#endif // QT_CONFIG(tooltip)
        incidenceAngleTitleLabel->setText(QCoreApplication::translate("TestPoints", "\346\234\200\345\244\247\345\205\245\345\260\204\350\247\222", nullptr));
#if QT_CONFIG(tooltip)
        incidenceAngleSpinBox->setToolTip(QCoreApplication::translate("TestPoints", "\345\217\215\345\260\204\347\220\203\345\274\200\345\217\243\346\263\225\345\220\221\344\270\216\342\200\234\345\217\215\345\260\204\347\220\203\346\214\207\345\220\221\344\273\252\345\231\250\342\200\235\346\226\271\345\220\221\344\271\213\351\227\264\345\205\201\350\256\270\347\232\204\346\234\200\345\244\247\345\244\271\350\247\222\343\200\202", nullptr));
#endif // QT_CONFIG(tooltip)
        incidenceAngleSpinBox->setSuffix(QCoreApplication::translate("TestPoints", "\302\260", nullptr));
        rotationStepTitleLabel->setText(QCoreApplication::translate("TestPoints", "\346\225\264\345\221\250\346\243\200\346\237\245\346\255\245\351\225\277", nullptr));
#if QT_CONFIG(tooltip)
        rotationStepSpinBox->setToolTip(QCoreApplication::translate("TestPoints", "\347\213\254\347\253\213\344\270\273\350\275\264J6\346\227\213\350\275\254\344\270\200\345\221\250\346\227\266\357\274\214\347\233\270\351\202\273\346\243\200\346\237\245\344\275\215\347\275\256\347\232\204\350\247\222\345\272\246\343\200\2025\302\260\345\257\271\345\272\22472\344\270\252\346\243\200\346\237\245\344\275\215\347\275\256\343\200\202", nullptr));
#endif // QT_CONFIG(tooltip)
        rotationStepSpinBox->setSuffix(QCoreApplication::translate("TestPoints", "\302\260", nullptr));
        trackerRangeInfoLabel->setText(QCoreApplication::translate("TestPoints", "J6\347\273\225TCP +Z\350\275\264\346\227\213\350\275\254\357\274\233\346\265\213\350\267\2350.8\357\275\236160 m\357\274\233\346\225\264\345\221\250\345\205\250\351\203\250\345\217\257\350\247\201\346\211\215\344\277\235\347\225\231", nullptr));
        showTrackerRangeCheckBox->setText(QCoreApplication::translate("TestPoints", "\346\230\276\347\244\272\350\214\203\345\233\264\346\250\241\345\236\213", nullptr));
        stlGroupBox->setTitle(QCoreApplication::translate("TestPoints", "STL \345\214\272\345\237\237\351\200\211\346\213\251", nullptr));
        loadStlButton->setText(QCoreApplication::translate("TestPoints", "\345\212\240\350\275\275 STL", nullptr));
        resetViewButton->setText(QCoreApplication::translate("TestPoints", "\351\207\215\347\275\256\350\247\206\350\247\222", nullptr));
        stlPathLabel->setText(QCoreApplication::translate("TestPoints", "\345\260\232\346\234\252\345\212\240\350\275\275 STL \346\250\241\345\236\213", nullptr));
        regionGroupBox->setTitle(QCoreApplication::translate("TestPoints", "\344\270\255\345\277\203\346\211\251\346\225\243\345\214\272\345\237\237\357\274\210\347\273\277\350\211\262\350\241\250\351\235\242\357\274\211", nullptr));
        regionSizeTitleLabel->setText(QCoreApplication::translate("TestPoints", "\346\211\251\346\225\243\350\214\203\345\233\264", nullptr));
        regionSizeValueLabel->setText(QCoreApplication::translate("TestPoints", "40%", nullptr));
        regionXTitleLabel->setText(QCoreApplication::translate("TestPoints", "\344\270\255\345\277\203 X", nullptr));
        regionXValueLabel->setText(QCoreApplication::translate("TestPoints", "--", nullptr));
        regionYTitleLabel->setText(QCoreApplication::translate("TestPoints", "\344\270\255\345\277\203 Y", nullptr));
        regionYValueLabel->setText(QCoreApplication::translate("TestPoints", "--", nullptr));
        regionZTitleLabel->setText(QCoreApplication::translate("TestPoints", "\344\270\255\345\277\203 Z", nullptr));
        regionZValueLabel->setText(QCoreApplication::translate("TestPoints", "--", nullptr));
        checkBox_filter->setText(QCoreApplication::translate("TestPoints", "\347\224\237\346\210\220\346\227\266\344\275\277\347\224\250\345\275\223\345\211\215\346\211\251\346\225\243\345\214\272\345\237\237\350\277\207\346\273\244", nullptr));
        regionBoundsLabel->setText(QCoreApplication::translate("TestPoints", "\350\257\267\345\212\240\350\275\275 STL \346\250\241\345\236\213", nullptr));
        resetRegionButton->setText(QCoreApplication::translate("TestPoints", "\346\201\242\345\244\215\351\273\230\350\256\244\344\270\255\345\277\203", nullptr));
        generationGroupBox->setTitle(QCoreApplication::translate("TestPoints", "\347\224\237\346\210\220\350\256\276\347\275\256", nullptr));
        label_count->setText(QCoreApplication::translate("TestPoints", "\347\224\237\346\210\220\347\202\271\346\225\260\357\274\232", nullptr));
        lineEdit_count->setPlaceholderText(QCoreApplication::translate("TestPoints", "\350\257\267\350\276\223\345\205\245\350\277\207\346\273\244\345\211\215\346\265\213\350\257\225\347\202\271\346\225\260\351\207\217", nullptr));
        label->setText(QCoreApplication::translate("TestPoints", "\351\242\204\350\256\241\347\224\237\346\210\220\347\202\271\346\225\260\357\274\232", nullptr));
        label_expected_count->setText(QCoreApplication::translate("TestPoints", "--", nullptr));
        previewTrackerButton->setText(QCoreApplication::translate("TestPoints", "\351\242\204\350\247\210\347\255\233\351\200\211", nullptr));
#if QT_CONFIG(tooltip)
        exportPreviewPoseButton->setToolTip(QCoreApplication::translate("TestPoints", "\346\265\213\350\257\225\345\212\237\350\203\275\357\274\232\345\257\274\345\207\272\346\234\200\347\273\210\344\277\235\347\225\231\347\202\271\347\232\204\345\205\263\350\212\202\343\200\201XYZ\343\200\201\345\216\237RX/RY\350\247\222\345\272\246\345\217\212\346\240\207\345\207\206ZYX\346\254\247\346\213\211\350\247\222\343\200\202", nullptr));
#endif // QT_CONFIG(tooltip)
        exportPreviewPoseButton->setText(QCoreApplication::translate("TestPoints", "\345\257\274\345\207\272\344\277\235\347\225\231\344\275\215\345\247\277", nullptr));
        pushButton_Confirm->setText(QCoreApplication::translate("TestPoints", "\347\224\237\346\210\220\345\271\266\344\277\235\345\255\230", nullptr));
        trackerResultLabel->setText(QCoreApplication::translate("TestPoints", "\346\234\200\347\273\210\347\255\233\351\200\211\357\274\232\345\260\232\346\234\252\351\242\204\350\247\210\n"
"\345\205\263\350\212\202\350\214\203\345\233\264\347\224\237\346\210\220\357\274\232--\343\200\200\345\216\273\351\207\215\357\274\232--\343\200\200\346\211\251\346\225\243\345\214\272\345\237\237\350\277\207\346\273\244\357\274\232--\343\200\200J6\346\225\264\345\221\250\350\277\207\346\273\244\357\274\232--", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestPoints: public Ui_TestPoints {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTPOINTS_H
