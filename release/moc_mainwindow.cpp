/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "startTcpServerRequested",
    "",
    "stopTcpServerRequested",
    "connectPcdmis",
    "disconnectPcdmis",
    "startPolling",
    "stopPolling",
    "startTcpServer",
    "stopTcpServer",
    "openTestPointsDialog",
    "captureCirclePoint",
    "deleteSelectedCirclePoints",
    "clearCirclePoints",
    "calculateCircle",
    "showCoordinate",
    "x",
    "y",
    "z",
    "finishCirclePointCapture",
    "requestId",
    "success",
    "coordinateMode",
    "errorMessage",
    "setTrackerOrigin",
    "showTrackingState",
    "TrackingState",
    "state",
    "message",
    "showConnectedState",
    "connected",
    "showPollingState",
    "polling",
    "showTcpServerState",
    "running",
    "listenAddress",
    "appendLog",
    "showError"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[76];
    char stringdata0[11];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[23];
    char stringdata4[14];
    char stringdata5[17];
    char stringdata6[13];
    char stringdata7[12];
    char stringdata8[15];
    char stringdata9[14];
    char stringdata10[21];
    char stringdata11[19];
    char stringdata12[27];
    char stringdata13[18];
    char stringdata14[16];
    char stringdata15[15];
    char stringdata16[2];
    char stringdata17[2];
    char stringdata18[2];
    char stringdata19[25];
    char stringdata20[10];
    char stringdata21[8];
    char stringdata22[15];
    char stringdata23[13];
    char stringdata24[17];
    char stringdata25[18];
    char stringdata26[14];
    char stringdata27[6];
    char stringdata28[8];
    char stringdata29[19];
    char stringdata30[10];
    char stringdata31[17];
    char stringdata32[8];
    char stringdata33[19];
    char stringdata34[8];
    char stringdata35[14];
    char stringdata36[10];
    char stringdata37[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 23),  // "startTcpServerRequested"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 22),  // "stopTcpServerRequested"
        QT_MOC_LITERAL(59, 13),  // "connectPcdmis"
        QT_MOC_LITERAL(73, 16),  // "disconnectPcdmis"
        QT_MOC_LITERAL(90, 12),  // "startPolling"
        QT_MOC_LITERAL(103, 11),  // "stopPolling"
        QT_MOC_LITERAL(115, 14),  // "startTcpServer"
        QT_MOC_LITERAL(130, 13),  // "stopTcpServer"
        QT_MOC_LITERAL(144, 20),  // "openTestPointsDialog"
        QT_MOC_LITERAL(165, 18),  // "captureCirclePoint"
        QT_MOC_LITERAL(184, 26),  // "deleteSelectedCirclePoints"
        QT_MOC_LITERAL(211, 17),  // "clearCirclePoints"
        QT_MOC_LITERAL(229, 15),  // "calculateCircle"
        QT_MOC_LITERAL(245, 14),  // "showCoordinate"
        QT_MOC_LITERAL(260, 1),  // "x"
        QT_MOC_LITERAL(262, 1),  // "y"
        QT_MOC_LITERAL(264, 1),  // "z"
        QT_MOC_LITERAL(266, 24),  // "finishCirclePointCapture"
        QT_MOC_LITERAL(291, 9),  // "requestId"
        QT_MOC_LITERAL(301, 7),  // "success"
        QT_MOC_LITERAL(309, 14),  // "coordinateMode"
        QT_MOC_LITERAL(324, 12),  // "errorMessage"
        QT_MOC_LITERAL(337, 16),  // "setTrackerOrigin"
        QT_MOC_LITERAL(354, 17),  // "showTrackingState"
        QT_MOC_LITERAL(372, 13),  // "TrackingState"
        QT_MOC_LITERAL(386, 5),  // "state"
        QT_MOC_LITERAL(392, 7),  // "message"
        QT_MOC_LITERAL(400, 18),  // "showConnectedState"
        QT_MOC_LITERAL(419, 9),  // "connected"
        QT_MOC_LITERAL(429, 16),  // "showPollingState"
        QT_MOC_LITERAL(446, 7),  // "polling"
        QT_MOC_LITERAL(454, 18),  // "showTcpServerState"
        QT_MOC_LITERAL(473, 7),  // "running"
        QT_MOC_LITERAL(481, 13),  // "listenAddress"
        QT_MOC_LITERAL(495, 9),  // "appendLog"
        QT_MOC_LITERAL(505, 9)   // "showError"
    },
    "MainWindow",
    "startTcpServerRequested",
    "",
    "stopTcpServerRequested",
    "connectPcdmis",
    "disconnectPcdmis",
    "startPolling",
    "stopPolling",
    "startTcpServer",
    "stopTcpServer",
    "openTestPointsDialog",
    "captureCirclePoint",
    "deleteSelectedCirclePoints",
    "clearCirclePoints",
    "calculateCircle",
    "showCoordinate",
    "x",
    "y",
    "z",
    "finishCirclePointCapture",
    "requestId",
    "success",
    "coordinateMode",
    "errorMessage",
    "setTrackerOrigin",
    "showTrackingState",
    "TrackingState",
    "state",
    "message",
    "showConnectedState",
    "connected",
    "showPollingState",
    "polling",
    "showTcpServerState",
    "running",
    "listenAddress",
    "appendLog",
    "showError"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  146,    2, 0x06,    1 /* Public */,
       3,    0,  147,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,  148,    2, 0x08,    3 /* Private */,
       5,    0,  149,    2, 0x08,    4 /* Private */,
       6,    0,  150,    2, 0x08,    5 /* Private */,
       7,    0,  151,    2, 0x08,    6 /* Private */,
       8,    0,  152,    2, 0x08,    7 /* Private */,
       9,    0,  153,    2, 0x08,    8 /* Private */,
      10,    0,  154,    2, 0x08,    9 /* Private */,
      11,    0,  155,    2, 0x08,   10 /* Private */,
      12,    0,  156,    2, 0x08,   11 /* Private */,
      13,    0,  157,    2, 0x08,   12 /* Private */,
      14,    0,  158,    2, 0x08,   13 /* Private */,
      15,    3,  159,    2, 0x08,   14 /* Private */,
      19,    7,  166,    2, 0x08,   18 /* Private */,
      24,    3,  181,    2, 0x08,   26 /* Private */,
      25,    2,  188,    2, 0x08,   30 /* Private */,
      29,    1,  193,    2, 0x08,   33 /* Private */,
      31,    1,  196,    2, 0x08,   35 /* Private */,
      33,    2,  199,    2, 0x08,   37 /* Private */,
      36,    1,  204,    2, 0x08,   40 /* Private */,
      37,    1,  207,    2, 0x08,   42 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   16,   17,   18,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Bool, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::QString,   20,   21,   16,   17,   18,   22,   23,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   16,   17,   18,
    QMetaType::Void, 0x80000000 | 26, QMetaType::QString,   27,   28,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   34,   35,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::QString,   28,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'startTcpServerRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopTcpServerRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectPcdmis'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disconnectPcdmis'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startPolling'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopPolling'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startTcpServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopTcpServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openTestPointsDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'captureCirclePoint'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteSelectedCirclePoints'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearCirclePoints'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'calculateCircle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showCoordinate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'finishCirclePointCapture'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint64, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setTrackerOrigin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'showTrackingState'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<TrackingState, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'showConnectedState'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'showPollingState'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'showTcpServerState'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'appendLog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'showError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->startTcpServerRequested(); break;
        case 1: _t->stopTcpServerRequested(); break;
        case 2: _t->connectPcdmis(); break;
        case 3: _t->disconnectPcdmis(); break;
        case 4: _t->startPolling(); break;
        case 5: _t->stopPolling(); break;
        case 6: _t->startTcpServer(); break;
        case 7: _t->stopTcpServer(); break;
        case 8: _t->openTestPointsDialog(); break;
        case 9: _t->captureCirclePoint(); break;
        case 10: _t->deleteSelectedCirclePoints(); break;
        case 11: _t->clearCirclePoints(); break;
        case 12: _t->calculateCircle(); break;
        case 13: _t->showCoordinate((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 14: _t->finishCirclePointCapture((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7]))); break;
        case 15: _t->setTrackerOrigin((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 16: _t->showTrackingState((*reinterpret_cast< std::add_pointer_t<TrackingState>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 17: _t->showConnectedState((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 18: _t->showPollingState((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 19: _t->showTcpServerState((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 20: _t->appendLog((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->showError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< TrackingState >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::startTcpServerRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::stopTcpServerRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::startTcpServerRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::stopTcpServerRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
