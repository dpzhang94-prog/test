/****************************************************************************
** Meta object code from reading C++ file 'pcdmisworker.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pcdmisworker.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pcdmisworker.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSPcdmisWorkerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSPcdmisWorkerENDCLASS = QtMocHelpers::stringData(
    "PcdmisWorker",
    "connectedChanged",
    "",
    "connected",
    "pollingChanged",
    "polling",
    "coordinateReceived",
    "x",
    "y",
    "z",
    "coordinateMode",
    "coordinateSampleFinished",
    "requestId",
    "success",
    "errorMessage",
    "trackerOriginChanged",
    "trackerOriginRefreshFinished",
    "trackingStateChanged",
    "TrackingState",
    "state",
    "message",
    "measurementValidityChanged",
    "valid",
    "reason",
    "logMessage",
    "errorOccurred",
    "initialize",
    "connectToPcdmis",
    "makeVisible",
    "disconnectFromPcdmis",
    "setCoordinateMode",
    "modeIndex",
    "setPollingEnabled",
    "enabled",
    "setPollingInterval",
    "milliseconds",
    "readOnce",
    "requestCoordinateSample",
    "refreshAlignedTrackerOrigin",
    "shutdown",
    "pollProbePosition",
    "onMachineReadoutExt",
    "onMachineEvent",
    "name",
    "argumentCount",
    "arguments",
    "onMachineError",
    "errorType",
    "onComException",
    "code",
    "source",
    "description",
    "help"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSPcdmisWorkerENDCLASS_t {
    uint offsetsAndSizes[106];
    char stringdata0[13];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[15];
    char stringdata5[8];
    char stringdata6[19];
    char stringdata7[2];
    char stringdata8[2];
    char stringdata9[2];
    char stringdata10[15];
    char stringdata11[25];
    char stringdata12[10];
    char stringdata13[8];
    char stringdata14[13];
    char stringdata15[21];
    char stringdata16[29];
    char stringdata17[21];
    char stringdata18[14];
    char stringdata19[6];
    char stringdata20[8];
    char stringdata21[27];
    char stringdata22[6];
    char stringdata23[7];
    char stringdata24[11];
    char stringdata25[14];
    char stringdata26[11];
    char stringdata27[16];
    char stringdata28[12];
    char stringdata29[21];
    char stringdata30[18];
    char stringdata31[10];
    char stringdata32[18];
    char stringdata33[8];
    char stringdata34[19];
    char stringdata35[13];
    char stringdata36[9];
    char stringdata37[24];
    char stringdata38[28];
    char stringdata39[9];
    char stringdata40[18];
    char stringdata41[20];
    char stringdata42[15];
    char stringdata43[5];
    char stringdata44[14];
    char stringdata45[10];
    char stringdata46[15];
    char stringdata47[10];
    char stringdata48[15];
    char stringdata49[5];
    char stringdata50[7];
    char stringdata51[12];
    char stringdata52[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSPcdmisWorkerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSPcdmisWorkerENDCLASS_t qt_meta_stringdata_CLASSPcdmisWorkerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "PcdmisWorker"
        QT_MOC_LITERAL(13, 16),  // "connectedChanged"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 9),  // "connected"
        QT_MOC_LITERAL(41, 14),  // "pollingChanged"
        QT_MOC_LITERAL(56, 7),  // "polling"
        QT_MOC_LITERAL(64, 18),  // "coordinateReceived"
        QT_MOC_LITERAL(83, 1),  // "x"
        QT_MOC_LITERAL(85, 1),  // "y"
        QT_MOC_LITERAL(87, 1),  // "z"
        QT_MOC_LITERAL(89, 14),  // "coordinateMode"
        QT_MOC_LITERAL(104, 24),  // "coordinateSampleFinished"
        QT_MOC_LITERAL(129, 9),  // "requestId"
        QT_MOC_LITERAL(139, 7),  // "success"
        QT_MOC_LITERAL(147, 12),  // "errorMessage"
        QT_MOC_LITERAL(160, 20),  // "trackerOriginChanged"
        QT_MOC_LITERAL(181, 28),  // "trackerOriginRefreshFinished"
        QT_MOC_LITERAL(210, 20),  // "trackingStateChanged"
        QT_MOC_LITERAL(231, 13),  // "TrackingState"
        QT_MOC_LITERAL(245, 5),  // "state"
        QT_MOC_LITERAL(251, 7),  // "message"
        QT_MOC_LITERAL(259, 26),  // "measurementValidityChanged"
        QT_MOC_LITERAL(286, 5),  // "valid"
        QT_MOC_LITERAL(292, 6),  // "reason"
        QT_MOC_LITERAL(299, 10),  // "logMessage"
        QT_MOC_LITERAL(310, 13),  // "errorOccurred"
        QT_MOC_LITERAL(324, 10),  // "initialize"
        QT_MOC_LITERAL(335, 15),  // "connectToPcdmis"
        QT_MOC_LITERAL(351, 11),  // "makeVisible"
        QT_MOC_LITERAL(363, 20),  // "disconnectFromPcdmis"
        QT_MOC_LITERAL(384, 17),  // "setCoordinateMode"
        QT_MOC_LITERAL(402, 9),  // "modeIndex"
        QT_MOC_LITERAL(412, 17),  // "setPollingEnabled"
        QT_MOC_LITERAL(430, 7),  // "enabled"
        QT_MOC_LITERAL(438, 18),  // "setPollingInterval"
        QT_MOC_LITERAL(457, 12),  // "milliseconds"
        QT_MOC_LITERAL(470, 8),  // "readOnce"
        QT_MOC_LITERAL(479, 23),  // "requestCoordinateSample"
        QT_MOC_LITERAL(503, 27),  // "refreshAlignedTrackerOrigin"
        QT_MOC_LITERAL(531, 8),  // "shutdown"
        QT_MOC_LITERAL(540, 17),  // "pollProbePosition"
        QT_MOC_LITERAL(558, 19),  // "onMachineReadoutExt"
        QT_MOC_LITERAL(578, 14),  // "onMachineEvent"
        QT_MOC_LITERAL(593, 4),  // "name"
        QT_MOC_LITERAL(598, 13),  // "argumentCount"
        QT_MOC_LITERAL(612, 9),  // "arguments"
        QT_MOC_LITERAL(622, 14),  // "onMachineError"
        QT_MOC_LITERAL(637, 9),  // "errorType"
        QT_MOC_LITERAL(647, 14),  // "onComException"
        QT_MOC_LITERAL(662, 4),  // "code"
        QT_MOC_LITERAL(667, 6),  // "source"
        QT_MOC_LITERAL(674, 11),  // "description"
        QT_MOC_LITERAL(686, 4)   // "help"
    },
    "PcdmisWorker",
    "connectedChanged",
    "",
    "connected",
    "pollingChanged",
    "polling",
    "coordinateReceived",
    "x",
    "y",
    "z",
    "coordinateMode",
    "coordinateSampleFinished",
    "requestId",
    "success",
    "errorMessage",
    "trackerOriginChanged",
    "trackerOriginRefreshFinished",
    "trackingStateChanged",
    "TrackingState",
    "state",
    "message",
    "measurementValidityChanged",
    "valid",
    "reason",
    "logMessage",
    "errorOccurred",
    "initialize",
    "connectToPcdmis",
    "makeVisible",
    "disconnectFromPcdmis",
    "setCoordinateMode",
    "modeIndex",
    "setPollingEnabled",
    "enabled",
    "setPollingInterval",
    "milliseconds",
    "readOnce",
    "requestCoordinateSample",
    "refreshAlignedTrackerOrigin",
    "shutdown",
    "pollProbePosition",
    "onMachineReadoutExt",
    "onMachineEvent",
    "name",
    "argumentCount",
    "arguments",
    "onMachineError",
    "errorType",
    "onComException",
    "code",
    "source",
    "description",
    "help"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSPcdmisWorkerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  170,    2, 0x06,    1 /* Public */,
       4,    1,  173,    2, 0x06,    3 /* Public */,
       6,    4,  176,    2, 0x06,    5 /* Public */,
      11,    7,  185,    2, 0x06,   10 /* Public */,
      15,    4,  200,    2, 0x06,   18 /* Public */,
      16,    5,  209,    2, 0x06,   23 /* Public */,
      17,    2,  220,    2, 0x06,   29 /* Public */,
      21,    2,  225,    2, 0x06,   32 /* Public */,
      24,    1,  230,    2, 0x06,   35 /* Public */,
      25,    1,  233,    2, 0x06,   37 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      26,    0,  236,    2, 0x0a,   39 /* Public */,
      27,    1,  237,    2, 0x0a,   40 /* Public */,
      27,    0,  240,    2, 0x2a,   42 /* Public | MethodCloned */,
      29,    0,  241,    2, 0x0a,   43 /* Public */,
      30,    1,  242,    2, 0x0a,   44 /* Public */,
      32,    1,  245,    2, 0x0a,   46 /* Public */,
      34,    1,  248,    2, 0x0a,   48 /* Public */,
      36,    0,  251,    2, 0x0a,   50 /* Public */,
      37,    1,  252,    2, 0x0a,   51 /* Public */,
      38,    0,  255,    2, 0x0a,   53 /* Public */,
      39,    0,  256,    2, 0x0a,   54 /* Public */,
      40,    0,  257,    2, 0x08,   55 /* Private */,
      41,    3,  258,    2, 0x08,   56 /* Private */,
      42,    3,  265,    2, 0x08,   60 /* Private */,
      46,    2,  272,    2, 0x08,   64 /* Private */,
      48,    4,  277,    2, 0x08,   67 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int,    7,    8,    9,   10,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Bool, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::QString,   12,   13,    7,    8,    9,   10,   14,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int,    7,    8,    9,   10,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QString,   13,    7,    8,    9,   14,
    QMetaType::Void, 0x80000000 | 18, QMetaType::QString,   19,   20,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   22,   23,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::QString,   20,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    7,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::VoidStar,   43,   44,   45,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   20,   47,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,   49,   50,   51,   52,

       0        // eod
};

Q_CONSTINIT const QMetaObject PcdmisWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSPcdmisWorkerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSPcdmisWorkerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSPcdmisWorkerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PcdmisWorker, std::true_type>,
        // method 'connectedChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'pollingChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'coordinateReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'coordinateSampleFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint64, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'trackerOriginChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'trackerOriginRefreshFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'trackingStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<TrackingState, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'measurementValidityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'logMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'initialize'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectToPcdmis'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'connectToPcdmis'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disconnectFromPcdmis'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setCoordinateMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setPollingEnabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setPollingInterval'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'readOnce'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'requestCoordinateSample'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint64, std::false_type>,
        // method 'refreshAlignedTrackerOrigin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'shutdown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pollProbePosition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMachineReadoutExt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'onMachineEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<void *, std::false_type>,
        // method 'onMachineError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onComException'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void PcdmisWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PcdmisWorker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connectedChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->pollingChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->coordinateReceived((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 3: _t->coordinateSampleFinished((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7]))); break;
        case 4: _t->trackerOriginChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 5: _t->trackerOriginRefreshFinished((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
        case 6: _t->trackingStateChanged((*reinterpret_cast< std::add_pointer_t<TrackingState>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->measurementValidityChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: _t->logMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->initialize(); break;
        case 11: _t->connectToPcdmis((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->connectToPcdmis(); break;
        case 13: _t->disconnectFromPcdmis(); break;
        case 14: _t->setCoordinateMode((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->setPollingEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 16: _t->setPollingInterval((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->readOnce(); break;
        case 18: _t->requestCoordinateSample((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1]))); break;
        case 19: _t->refreshAlignedTrackerOrigin(); break;
        case 20: _t->shutdown(); break;
        case 21: _t->pollProbePosition(); break;
        case 22: _t->onMachineReadoutExt((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 23: _t->onMachineEvent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<void*>>(_a[3]))); break;
        case 24: _t->onMachineError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 25: _t->onComException((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
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
            using _t = void (PcdmisWorker::*)(bool );
            if (_t _q_method = &PcdmisWorker::connectedChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PcdmisWorker::*)(bool );
            if (_t _q_method = &PcdmisWorker::pollingChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PcdmisWorker::*)(double , double , double , int );
            if (_t _q_method = &PcdmisWorker::coordinateReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PcdmisWorker::*)(quint64 , bool , double , double , double , int , const QString & );
            if (_t _q_method = &PcdmisWorker::coordinateSampleFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PcdmisWorker::*)(double , double , double , int );
            if (_t _q_method = &PcdmisWorker::trackerOriginChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PcdmisWorker::*)(bool , double , double , double , const QString & );
            if (_t _q_method = &PcdmisWorker::trackerOriginRefreshFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PcdmisWorker::*)(TrackingState , const QString & );
            if (_t _q_method = &PcdmisWorker::trackingStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PcdmisWorker::*)(bool , const QString & );
            if (_t _q_method = &PcdmisWorker::measurementValidityChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PcdmisWorker::*)(const QString & );
            if (_t _q_method = &PcdmisWorker::logMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PcdmisWorker::*)(const QString & );
            if (_t _q_method = &PcdmisWorker::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject *PcdmisWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PcdmisWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSPcdmisWorkerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PcdmisWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void PcdmisWorker::connectedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PcdmisWorker::pollingChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PcdmisWorker::coordinateReceived(double _t1, double _t2, double _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PcdmisWorker::coordinateSampleFinished(quint64 _t1, bool _t2, double _t3, double _t4, double _t5, int _t6, const QString & _t7)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PcdmisWorker::trackerOriginChanged(double _t1, double _t2, double _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PcdmisWorker::trackerOriginRefreshFinished(bool _t1, double _t2, double _t3, double _t4, const QString & _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PcdmisWorker::trackingStateChanged(TrackingState _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PcdmisWorker::measurementValidityChanged(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PcdmisWorker::logMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void PcdmisWorker::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
