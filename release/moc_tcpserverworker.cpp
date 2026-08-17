/****************************************************************************
** Meta object code from reading C++ file 'tcpserverworker.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tcpserverworker.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpserverworker.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSTcpServerWorkerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSTcpServerWorkerENDCLASS = QtMocHelpers::stringData(
    "TcpServerWorker",
    "serverStateChanged",
    "",
    "running",
    "listenAddress",
    "logMessage",
    "message",
    "businessRequestReceived",
    "requestToken",
    "payload",
    "startServer",
    "stopServer",
    "completeBusinessRequest",
    "data",
    "discardBusinessRequest",
    "onNewConnection",
    "onReadyRead",
    "onClientDisconnected"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTcpServerWorkerENDCLASS_t {
    uint offsetsAndSizes[36];
    char stringdata0[16];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[14];
    char stringdata5[11];
    char stringdata6[8];
    char stringdata7[24];
    char stringdata8[13];
    char stringdata9[8];
    char stringdata10[12];
    char stringdata11[11];
    char stringdata12[24];
    char stringdata13[5];
    char stringdata14[23];
    char stringdata15[16];
    char stringdata16[12];
    char stringdata17[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTcpServerWorkerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTcpServerWorkerENDCLASS_t qt_meta_stringdata_CLASSTcpServerWorkerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "TcpServerWorker"
        QT_MOC_LITERAL(16, 18),  // "serverStateChanged"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 7),  // "running"
        QT_MOC_LITERAL(44, 13),  // "listenAddress"
        QT_MOC_LITERAL(58, 10),  // "logMessage"
        QT_MOC_LITERAL(69, 7),  // "message"
        QT_MOC_LITERAL(77, 23),  // "businessRequestReceived"
        QT_MOC_LITERAL(101, 12),  // "requestToken"
        QT_MOC_LITERAL(114, 7),  // "payload"
        QT_MOC_LITERAL(122, 11),  // "startServer"
        QT_MOC_LITERAL(134, 10),  // "stopServer"
        QT_MOC_LITERAL(145, 23),  // "completeBusinessRequest"
        QT_MOC_LITERAL(169, 4),  // "data"
        QT_MOC_LITERAL(174, 22),  // "discardBusinessRequest"
        QT_MOC_LITERAL(197, 15),  // "onNewConnection"
        QT_MOC_LITERAL(213, 11),  // "onReadyRead"
        QT_MOC_LITERAL(225, 20)   // "onClientDisconnected"
    },
    "TcpServerWorker",
    "serverStateChanged",
    "",
    "running",
    "listenAddress",
    "logMessage",
    "message",
    "businessRequestReceived",
    "requestToken",
    "payload",
    "startServer",
    "stopServer",
    "completeBusinessRequest",
    "data",
    "discardBusinessRequest",
    "onNewConnection",
    "onReadyRead",
    "onClientDisconnected"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTcpServerWorkerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   74,    2, 0x06,    1 /* Public */,
       5,    1,   79,    2, 0x06,    4 /* Public */,
       7,    2,   82,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,   87,    2, 0x0a,    9 /* Public */,
      11,    0,   88,    2, 0x0a,   10 /* Public */,
      12,    2,   89,    2, 0x0a,   11 /* Public */,
      14,    1,   94,    2, 0x0a,   14 /* Public */,
      15,    0,   97,    2, 0x08,   16 /* Private */,
      16,    0,   98,    2, 0x08,   17 /* Private */,
      17,    0,   99,    2, 0x08,   18 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::QString,    8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::QString,    8,   13,
    QMetaType::Void, QMetaType::ULongLong,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject TcpServerWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSTcpServerWorkerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTcpServerWorkerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTcpServerWorkerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TcpServerWorker, std::true_type>,
        // method 'serverStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'logMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'businessRequestReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint64, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'startServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'completeBusinessRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint64, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'discardBusinessRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint64, std::false_type>,
        // method 'onNewConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReadyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClientDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TcpServerWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TcpServerWorker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->serverStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->logMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->businessRequestReceived((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->startServer(); break;
        case 4: _t->stopServer(); break;
        case 5: _t->completeBusinessRequest((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->discardBusinessRequest((*reinterpret_cast< std::add_pointer_t<quint64>>(_a[1]))); break;
        case 7: _t->onNewConnection(); break;
        case 8: _t->onReadyRead(); break;
        case 9: _t->onClientDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TcpServerWorker::*)(bool , const QString & );
            if (_t _q_method = &TcpServerWorker::serverStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TcpServerWorker::*)(const QString & );
            if (_t _q_method = &TcpServerWorker::logMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TcpServerWorker::*)(quint64 , const QString & );
            if (_t _q_method = &TcpServerWorker::businessRequestReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *TcpServerWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpServerWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTcpServerWorkerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TcpServerWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void TcpServerWorker::serverStateChanged(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpServerWorker::logMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TcpServerWorker::businessRequestReceived(quint64 _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
