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
    "completeTcpBusinessRequestRequested",
    "requestToken",
    "data",
    "discardTcpBusinessRequestRequested",
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
    "exportCircleResults",
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
    "handleRobotBusinessRequest",
    "payload",
    "appendLog",
    "showError"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[90];
    char stringdata0[11];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[23];
    char stringdata4[36];
    char stringdata5[13];
    char stringdata6[5];
    char stringdata7[35];
    char stringdata8[14];
    char stringdata9[17];
    char stringdata10[13];
    char stringdata11[12];
    char stringdata12[15];
    char stringdata13[14];
    char stringdata14[21];
    char stringdata15[19];
    char stringdata16[27];
    char stringdata17[18];
    char stringdata18[16];
    char stringdata19[20];
    char stringdata20[15];
    char stringdata21[2];
    char stringdata22[2];
    char stringdata23[2];
    char stringdata24[25];
    char stringdata25[10];
    char stringdata26[8];
    char stringdata27[15];
    char stringdata28[13];
    char stringdata29[17];
    char stringdata30[18];
    char stringdata31[14];
    char stringdata32[6];
    char stringdata33[8];
    char stringdata34[19];
    char stringdata35[10];
    char stringdata36[17];
    char stringdata37[8];
    char stringdata38[19];
    char stringdata39[8];
    char stringdata40[14];
    char stringdata41[27];
    char stringdata42[8];
    char stringdata43[10];
    char stringdata44[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 23),  // "startTcpServerRequested"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 22),  // "stopTcpServerRequested"
        QT_MOC_LITERAL(59, 35),  // "completeTcpBusinessRequestReq..."
        QT_MOC_LITERAL(95, 12),  // "requestToken"
        QT_MOC_LITERAL(108, 4),  // "data"
        QT_MOC_LITERAL(113, 34),  // "discardTcpBusinessRequestRequ..."
        QT_MOC_LITERAL(148, 13),  // "connectPcdmis"
        QT_MOC_LITERAL(162, 16),  // "disconnectPcdmis"
        QT_MOC_LITERAL(179, 12),  // "startPolling"
        QT_MOC_LITERAL(192, 11),  // "stopPolling"
        QT_MOC_LITERAL(204, 14),  // "startTcpServer"
        QT_MOC_LITERAL(219, 13),  // "stopTcpServer"
        QT_MOC_LITERAL(233, 20),  // "openTestPointsDialog"
        QT_MOC_LITERAL(254, 18),  // "captureCirclePoint"
        QT_MOC_LITERAL(273, 26),  // "deleteSelectedCirclePoints"
        QT_MOC_LITERAL(300, 17),  // "clearCirclePoints"
        QT_MOC_LITERAL(318, 15),  // "calculateCircle"
        QT_MOC_LITERAL(334, 19),  // "exportCircleResults"
        QT_MOC_LITERAL(354, 14),  // "showCoordinate"
        QT_MOC_LITERAL(369, 1),  // "x"
        QT_MOC_LITERAL(371, 1),  // "y"
        QT_MOC_LITERAL(373, 1),  // "z"
        QT_MOC_LITERAL(375, 24),  // "finishCirclePointCapture"
        QT_MOC_LITERAL(400, 9),  // "requestId"
        QT_MOC_LITERAL(410, 7),  // "success"
        QT_MOC_LITERAL(418, 14),  // "coordinateMode"
        QT_MOC_LITERAL(433, 12),  // "errorMessage"
        QT_MOC_LITERAL(446, 16),  // "setTrackerOrigin"
        QT_MOC_LITERAL(463, 17),  // "showTrackingState"
        QT_MOC_LITERAL(481, 13),  // "TrackingState"
        QT_MOC_LITERAL(495, 5),  // "state"
        QT_MOC_LITERAL(501, 7),  // "message"
        QT_MOC_LITERAL(509, 18),  // "showConnectedState"
        QT_MOC_LITERAL(528, 9),  // "connected"
        QT_MOC_LITERAL(538, 16),  // "showPollingState"
        QT_MOC_LITERAL(555, 7),  // "polling"
        QT_MOC_LITERAL(563, 18),  // "showTcpServerState"
        QT_MOC_LITERAL(582, 7),  // "running"
        QT_MOC_LITERAL(590, 13),  // "listenAddress"
        QT_MOC_LITERAL(604, 26),  // "handleRobotBusinessRequest"
        QT_MOC_LITERAL(631, 7),  // "payload"
        QT_MOC_LITERAL(639, 9),  // "appendLog"
        QT_MOC_LITERAL(649, 9)   // "showError"
    },
    "MainWindow",
    "startTcpServerRequested",
    "",
    "stopTcpServerRequested",
    "completeTcpBusinessRequestRequested",
    "requestToken",
    "data",
    "discardTcpBusinessRequestRequested",
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
    "exportCircleResults",
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
    "handleRobotBusinessRequest",
    "payload",
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
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  170,    2, 0x06,    1 /* Public */,
       3,    0,  171,    2, 0x06,    2 /* Public */,
       4,    2,  172,    2, 0x06,    3 /* Public */,
       7,    1,  177,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,  180,    2, 0x08,    8 /* Private */,
       9,    0,  181,    2, 0x08,    9 /* Private */,
      10,    0,  182,    2, 0x08,   10 /* Private */,
      11,    0,  183,    2, 0x08,   11 /* Private */,
      12,    0,  184,    2, 0x08,   12 /* Private */,
      13,    0,  185,    2, 0x08,   13 /* Private */,
      14,    0,  186,    2, 0x08,   14 /* Private */,
      15,    0,  187,    2, 0x08,   15 /* Private */,
      16,    0,  188,    2, 0x08,   16 /* Private */,
      17,    0,  189,    2, 0x08,   17 /* Private */,
      18,    0,  190,    2, 0x08,   18 /* Private */,
      19,    0,  191,    2, 0x08,   19 /* Private */,
      20,    3,  192,    2, 0x08,   20 /* Private */,
      24,    7,  199,    2, 0x08,   24 /* Private */,
      29,    3,  214,    2, 0x08,   32 /* Private */,
      30,    2,  221,    2, 0x08,   36 /* Private */,
      34,    1,  226,    2, 0x08,   39 /* Private */,
      36,    1,  229,    2, 0x08,   41 /* Private */,
      38,    2,  232,    2, 0x08,   43 /* Private */,
      41,    2,  237,    2, 0x08,   46 /* Private */,
      43,    1,  242,    2, 0x08,   49 /* Private */,
      44,    1,  245,    2, 0x08,   51 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::ULongLong,    5,

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
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   21,   22,   23,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Bool, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::QString,   25,   26,   21,   22,   23,   27,   28,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   21,   22,   23,
    QMetaType::Void, 0x80000000 | 31, QMetaType::QString,   32,   33,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Bool,   37,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   39,   40,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::QString,    5,   42,
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void, QMetaType::QString,   33,

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
        // method 'completeTcpBusinessRequestRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint64, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'discardTcpBusinessRequestRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint64, std::false_type>,
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
        // method 'exportCircleResults'
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
        // method 'handleRobotBusinessRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint64, std::false_type>,
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
        case 2: _t->completeTcpBusinessRequestRequested((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->discardTcpBusinessRequestRequested((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1]))); break;
        case 4: _t->connectPcdmis(); break;
        case 5: _t->disconnectPcdmis(); break;
        case 6: _t->startPolling(); break;
        case 7: _t->stopPolling(); break;
        case 8: _t->startTcpServer(); break;
        case 9: _t->stopTcpServer(); break;
        case 10: _t->openTestPointsDialog(); break;
        case 11: _t->captureCirclePoint(); break;
        case 12: _t->deleteSelectedCirclePoints(); break;
        case 13: _t->clearCirclePoints(); break;
        case 14: _t->calculateCircle(); break;
        case 15: _t->exportCircleResults(); break;
        case 16: _t->showCoordinate((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 17: _t->finishCirclePointCapture((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7]))); break;
        case 18: _t->setTrackerOrigin((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 19: _t->showTrackingState((*reinterpret_cast< std::add_pointer_t<TrackingState>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 20: _t->showConnectedState((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 21: _t->showPollingState((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 22: _t->showTcpServerState((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 23: _t->handleRobotBusinessRequest((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 24: _t->appendLog((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 25: _t->showError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 19:
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
        {
            using _t = void (MainWindow::*)(quint64 , const QString & );
            if (_t _q_method = &MainWindow::completeTcpBusinessRequestRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(quint64 );
            if (_t _q_method = &MainWindow::discardTcpBusinessRequestRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
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
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
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

// SIGNAL 2
void MainWindow::completeTcpBusinessRequestRequested(quint64 _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::discardTcpBusinessRequestRequested(quint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
