QT += core gui widgets network openglwidgets axcontainer

CONFIG += c++17
DEFINES += NOMINMAX
TEMPLATE = app
TARGET = PCDMIS_Qt_Test

SOURCES += \
    features/testpoints/testpoints.cpp \
    geometrycalculator.cpp \
    main.cpp \
    mainwindow.cpp \
    pcdmisclient.cpp \
    pcdmisworker.cpp \
    robotkinematics.cpp \
    tcpserverworker.cpp

HEADERS += \
    features/testpoints/testpoints.h \
    geometrycalculator.h \
    mainwindow.h \
    pcdmisclient.h \
    pcdmisworker.h \
    robotkinematics.h \
    tcpserverworker.h \
    trackingstate.h

FORMS += \
    features/testpoints/testpoints.ui \
    mainwindow.ui

include($$PWD/thirdparty/kinematics/kinematics.pri)
include($$PWD/thirdparty/vtk/vtk.pri)

win32:CONFIG += windows
