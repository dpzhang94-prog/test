/****************************************************************************
** Meta object code from reading C++ file 'pcdmisclient.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pcdmisclient.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pcdmisclient.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSPcdmisClientENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSPcdmisClientENDCLASS = QtMocHelpers::stringData(
    "PcdmisClient",
    "connectedChanged",
    "",
    "connected",
    "pollingChanged",
    "polling",
    "coordinateReceived",
    "x",
    "y",
    "z",
    "coordinateSampleFinished",
    "requestId",
    "success",
    "coordinateMode",
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
    "connectRequested",
    "makeVisible",
    "disconnectRequested",
    "coordinateModeRequested",
    "modeIndex",
    "pollingEnabledRequested",
    "enabled",
    "pollingIntervalRequested",
    "milliseconds",
    "readOnceRequested",
    "coordinateSampleRequested",
    "trackerOriginRefreshRequested",
    "connectToPcdmis",
    "disconnectFromPcdmis",
    "setCoordinateMode",
    "setPollingEnabled",
    "setPollingInterval",
    "readOnce",
    "requestCoordinateSample",
    "refreshAlignedTrackerOrigin",
    "handleWorkerConnectedChanged",
    "handleWorkerPollingChanged",
    "handleWorkerCoordinate",
    "handleWorkerTrackerOrigin",
    "handleWorkerTrackerOriginRefreshFinished"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSPcdmisClientENDCLASS_t {
    uint offsetsAndSizes[102];
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
    char stringdata10[25];
    char stringdata11[10];
    char stringdata12[8];
    char stringdata13[15];
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
    char stringdata26[17];
    char stringdata27[12];
    char stringdata28[20];
    char stringdata29[24];
    char stringdata30[10];
    char stringdata31[24];
    char stringdata32[8];
    char stringdata33[25];
    char stringdata34[13];
    char stringdata35[18];
    char stringdata36[26];
    char stringdata37[30];
    char stringdata38[16];
    char stringdata39[21];
    char stringdata40[18];
    char stringdata41[18];
    char stringdata42[19];
    char stringdata43[9];
    char stringdata44[24];
    char stringdata45[28];
    char stringdata46[29];
    char stringdata47[27];
    char stringdata48[23];
    char stringdata49[26];
    char stringdata50[41];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSPcdmisClientENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSPcdmisClientENDCLASS_t qt_meta_stringdata_CLASSPcdmisClientENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "PcdmisClient"
        QT_MOC_LITERAL(13, 16),  // "connectedChanged"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 9),  // "connected"
        QT_MOC_LITERAL(41, 14),  // "pollingChanged"
        QT_MOC_LITERAL(56, 7),  // "polling"
        QT_MOC_LITERAL(64, 18),  // "coordinateReceived"
        QT_MOC_LITERAL(83, 1),  // "x"
        QT_MOC_LITERAL(85, 1),  // "y"
        QT_MOC_LITERAL(87, 1),  // "z"
        QT_MOC_LITERAL(89, 24),  // "coordinateSampleFinished"
        QT_MOC_LITERAL(114, 9),  // "requestId"
        QT_MOC_LITERAL(124, 7),  // "success"
        QT_MOC_LITERAL(132, 14),  // "coordinateMode"
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
        QT_MOC_LITERAL(324, 16),  // "connectRequested"
        QT_MOC_LITERAL(341, 11),  // "makeVisible"
        QT_MOC_LITERAL(353, 19),  // "disconnectRequested"
        QT_MOC_LITERAL(373, 23),  // "coordinateModeRequested"
        QT_MOC_LITERAL(397, 9),  // "modeIndex"
        QT_MOC_LITERAL(407, 23),  // "pollingEnabledRequested"
        QT_MOC_LITERAL(431, 7),  // "enabled"
        QT_MOC_LITERAL(439, 24),  // "pollingIntervalRequested"
        QT_MOC_LITERAL(464, 12),  // "milliseconds"
        QT_MOC_LITERAL(477, 17),  // "readOnceRequested"
        QT_MOC_LITERAL(495, 25),  // "coordinateSampleRequested"
        QT_MOC_LITERAL(521, 29),  // "trackerOriginRefreshRequested"
        QT_MOC_LITERAL(551, 15),  // "connectToPcdmis"
        QT_MOC_LITERAL(567, 20),  // "disconnectFromPcdmis"
        QT_MOC_LITERAL(588, 17),  // "setCoordinateMode"
        QT_MOC_LITERAL(606, 17),  // "setPollingEnabled"
        QT_MOC_LITERAL(624, 18),  // "setPollingInterval"
        QT_MOC_LITERAL(643, 8),  // "readOnce"
        QT_MOC_LITERAL(652, 23),  // "requestCoordinateSample"
        QT_MOC_LITERAL(676, 27),  // "refreshAlignedTrackerOrigin"
        QT_MOC_LITERAL(704, 28),  // "handleWorkerConnectedChanged"
        QT_MOC_LITERAL(733, 26),  // "handleWorkerPollingChanged"
        QT_MOC_LITERAL(760, 22),  // "handleWorkerCoordinate"
        QT_MOC_LITERAL(783, 25),  // "handleWorkerTrackerOrigin"
        QT_MOC_LITERAL(809, 40)   // "handleWorkerTrackerOriginRefr..."
    },
    "PcdmisClient",
    "connectedChanged",
    "",
    "connected",
    "pollingChanged",
    "polling",
    "coordinateReceived",
    "x",
    "y",
    "z",
    "coordinateSampleFinished",
    "requestId",
    "success",
    "coordinateMode",
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
    "connectRequested",
    "makeVisible",
    "disconnectRequested",
    "coordinateModeRequested",
    "modeIndex",
    "pollingEnabledRequested",
    "enabled",
    "pollingIntervalRequested",
    "milliseconds",
    "readOnceRequested",
    "coordinateSampleRequested",
    "trackerOriginRefreshRequested",
    "connectToPcdmis",
    "disconnectFromPcdmis",
    "setCoordinateMode",
    "setPollingEnabled",
    "setPollingInterval",
    "readOnce",
    "requestCoordinateSample",
    "refreshAlignedTrackerOrigin",
    "handleWorkerConnectedChanged",
    "handleWorkerPollingChanged",
    "handleWorkerCoordinate",
    "handleWorkerTrackerOrigin",
    "handleWorkerTrackerOriginRefreshFinished"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSPcdmisClientENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  206,    2, 0x06,    1 /* Public */,
       4,    1,  209,    2, 0x06,    3 /* Public */,
       6,    3,  212,    2, 0x06,    5 /* Public */,
      10,    7,  219,    2, 0x06,    9 /* Public */,
      15,    3,  234,    2, 0x06,   17 /* Public */,
      16,    5,  241,    2, 0x06,   21 /* Public */,
      17,    2,  252,    2, 0x06,   27 /* Public */,
      21,    2,  257,    2, 0x06,   30 /* Public */,
      24,    1,  262,    2, 0x06,   33 /* Public */,
      25,    1,  265,    2, 0x06,   35 /* Public */,
      26,    1,  268,    2, 0x06,   37 /* Public */,
      28,    0,  271,    2, 0x06,   39 /* Public */,
      29,    1,  272,    2, 0x06,   40 /* Public */,
      31,    1,  275,    2, 0x06,   42 /* Public */,
      33,    1,  278,    2, 0x06,   44 /* Public */,
      35,    0,  281,    2, 0x06,   46 /* Public */,
      36,    1,  282,    2, 0x06,   47 /* Public */,
      37,    0,  285,    2, 0x06,   49 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      38,    1,  286,    2, 0x0a,   50 /* Public */,
      38,    0,  289,    2, 0x2a,   52 /* Public | MethodCloned */,
      39,    0,  290,    2, 0x0a,   53 /* Public */,
      40,    1,  291,    2, 0x0a,   54 /* Public */,
      41,    1,  294,    2, 0x0a,   56 /* Public */,
      42,    1,  297,    2, 0x0a,   58 /* Public */,
      43,    0,  300,    2, 0x0a,   60 /* Public */,
      44,    1,  301,    2, 0x0a,   61 /* Public */,
      45,    0,  304,    2, 0x0a,   63 /* Public */,
      46,    1,  305,    2, 0x08,   64 /* Private */,
      47,    1,  308,    2, 0x08,   66 /* Private */,
      48,    4,  311,    2, 0x08,   68 /* Private */,
      49,    4,  320,    2, 0x08,   73 /* Private */,
      50,    5,  329,    2, 0x08,   78 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    7,    8,    9,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Bool, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::QString,   11,   12,    7,    8,    9,   13,   14,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    7,    8,    9,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QString,   12,    7,    8,    9,   14,
    QMetaType::Void, 0x80000000 | 18, QMetaType::QString,   19,   20,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   22,   23,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::Bool,   27,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong,   11,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int,    7,    8,    9,   13,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int,    7,    8,    9,   13,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QString,   12,    7,    8,    9,   14,

       0        // eod
};

Q_CONSTINIT const QMetaObject PcdmisClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSPcdmisClientENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSPcdmisClientENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSPcdmisClientENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PcdmisClient, std::true_type>,
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
        // method 'connectRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'disconnectRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'coordinateModeRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'pollingEnabledRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'pollingIntervalRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'readOnceRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'coordinateSampleRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint64, std::false_type>,
        // method 'trackerOriginRefreshRequested'
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
        // method 'handleWorkerConnectedChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleWorkerPollingChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'handleWorkerCoordinate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleWorkerTrackerOrigin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleWorkerTrackerOriginRefreshFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void PcdmisClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PcdmisClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connectedChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->pollingChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->coordinateReceived((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 3: _t->coordinateSampleFinished((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7]))); break;
        case 4: _t->trackerOriginChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 5: _t->trackerOriginRefreshFinished((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
        case 6: _t->trackingStateChanged((*reinterpret_cast< std::add_pointer_t<TrackingState>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->measurementValidityChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: _t->logMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->connectRequested((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->disconnectRequested(); break;
        case 12: _t->coordinateModeRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->pollingEnabledRequested((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->pollingIntervalRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->readOnceRequested(); break;
        case 16: _t->coordinateSampleRequested((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1]))); break;
        case 17: _t->trackerOriginRefreshRequested(); break;
        case 18: _t->connectToPcdmis((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 19: _t->connectToPcdmis(); break;
        case 20: _t->disconnectFromPcdmis(); break;
        case 21: _t->setCoordinateMode((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 22: _t->setPollingEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 23: _t->setPollingInterval((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 24: _t->readOnce(); break;
        case 25: _t->requestCoordinateSample((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1]))); break;
        case 26: _t->refreshAlignedTrackerOrigin(); break;
        case 27: _t->handleWorkerConnectedChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 28: _t->handleWorkerPollingChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 29: _t->handleWorkerCoordinate((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 30: _t->handleWorkerTrackerOrigin((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 31: _t->handleWorkerTrackerOriginRefreshFinished((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
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
            using _t = void (PcdmisClient::*)(bool );
            if (_t _q_method = &PcdmisClient::connectedChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(bool );
            if (_t _q_method = &PcdmisClient::pollingChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(double , double , double );
            if (_t _q_method = &PcdmisClient::coordinateReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(quint64 , bool , double , double , double , int , const QString & );
            if (_t _q_method = &PcdmisClient::coordinateSampleFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(double , double , double );
            if (_t _q_method = &PcdmisClient::trackerOriginChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(bool , double , double , double , const QString & );
            if (_t _q_method = &PcdmisClient::trackerOriginRefreshFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(TrackingState , const QString & );
            if (_t _q_method = &PcdmisClient::trackingStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(bool , const QString & );
            if (_t _q_method = &PcdmisClient::measurementValidityChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(const QString & );
            if (_t _q_method = &PcdmisClient::logMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(const QString & );
            if (_t _q_method = &PcdmisClient::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(bool );
            if (_t _q_method = &PcdmisClient::connectRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)();
            if (_t _q_method = &PcdmisClient::disconnectRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(int );
            if (_t _q_method = &PcdmisClient::coordinateModeRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(bool );
            if (_t _q_method = &PcdmisClient::pollingEnabledRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(int );
            if (_t _q_method = &PcdmisClient::pollingIntervalRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)();
            if (_t _q_method = &PcdmisClient::readOnceRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)(quint64 );
            if (_t _q_method = &PcdmisClient::coordinateSampleRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (PcdmisClient::*)();
            if (_t _q_method = &PcdmisClient::trackerOriginRefreshRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 17;
                return;
            }
        }
    }
}

const QMetaObject *PcdmisClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PcdmisClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSPcdmisClientENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PcdmisClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}

// SIGNAL 0
void PcdmisClient::connectedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PcdmisClient::pollingChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PcdmisClient::coordinateReceived(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PcdmisClient::coordinateSampleFinished(quint64 _t1, bool _t2, double _t3, double _t4, double _t5, int _t6, const QString & _t7)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PcdmisClient::trackerOriginChanged(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PcdmisClient::trackerOriginRefreshFinished(bool _t1, double _t2, double _t3, double _t4, const QString & _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PcdmisClient::trackingStateChanged(TrackingState _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PcdmisClient::measurementValidityChanged(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PcdmisClient::logMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void PcdmisClient::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void PcdmisClient::connectRequested(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void PcdmisClient::disconnectRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void PcdmisClient::coordinateModeRequested(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void PcdmisClient::pollingEnabledRequested(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void PcdmisClient::pollingIntervalRequested(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void PcdmisClient::readOnceRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void PcdmisClient::coordinateSampleRequested(quint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void PcdmisClient::trackerOriginRefreshRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}
QT_WARNING_POP
