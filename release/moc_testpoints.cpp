/****************************************************************************
** Meta object code from reading C++ file 'testpoints.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../features/testpoints/testpoints.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testpoints.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSTestPointsENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSTestPointsENDCLASS = QtMocHelpers::stringData(
    "TestPoints",
    "signal_path",
    "",
    "path",
    "on_pushButton_Confirm_clicked",
    "on_lineEdit_count_editingFinished",
    "refreshTrackerPosition",
    "handleTrackerOriginRefreshFinished",
    "success",
    "x",
    "y",
    "z",
    "errorMessage",
    "useTestTrackerPosition",
    "previewTrackerVisibility",
    "exportPreviewRetainedPoses"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTestPointsENDCLASS_t {
    uint offsetsAndSizes[32];
    char stringdata0[11];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[30];
    char stringdata5[34];
    char stringdata6[23];
    char stringdata7[35];
    char stringdata8[8];
    char stringdata9[2];
    char stringdata10[2];
    char stringdata11[2];
    char stringdata12[13];
    char stringdata13[23];
    char stringdata14[25];
    char stringdata15[27];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTestPointsENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTestPointsENDCLASS_t qt_meta_stringdata_CLASSTestPointsENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "TestPoints"
        QT_MOC_LITERAL(11, 11),  // "signal_path"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 4),  // "path"
        QT_MOC_LITERAL(29, 29),  // "on_pushButton_Confirm_clicked"
        QT_MOC_LITERAL(59, 33),  // "on_lineEdit_count_editingFini..."
        QT_MOC_LITERAL(93, 22),  // "refreshTrackerPosition"
        QT_MOC_LITERAL(116, 34),  // "handleTrackerOriginRefreshFin..."
        QT_MOC_LITERAL(151, 7),  // "success"
        QT_MOC_LITERAL(159, 1),  // "x"
        QT_MOC_LITERAL(161, 1),  // "y"
        QT_MOC_LITERAL(163, 1),  // "z"
        QT_MOC_LITERAL(165, 12),  // "errorMessage"
        QT_MOC_LITERAL(178, 22),  // "useTestTrackerPosition"
        QT_MOC_LITERAL(201, 24),  // "previewTrackerVisibility"
        QT_MOC_LITERAL(226, 26)   // "exportPreviewRetainedPoses"
    },
    "TestPoints",
    "signal_path",
    "",
    "path",
    "on_pushButton_Confirm_clicked",
    "on_lineEdit_count_editingFinished",
    "refreshTrackerPosition",
    "handleTrackerOriginRefreshFinished",
    "success",
    "x",
    "y",
    "z",
    "errorMessage",
    "useTestTrackerPosition",
    "previewTrackerVisibility",
    "exportPreviewRetainedPoses"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTestPointsENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   65,    2, 0x08,    3 /* Private */,
       5,    0,   66,    2, 0x08,    4 /* Private */,
       6,    0,   67,    2, 0x08,    5 /* Private */,
       7,    5,   68,    2, 0x08,    6 /* Private */,
      13,    0,   79,    2, 0x08,   12 /* Private */,
      14,    0,   80,    2, 0x08,   13 /* Private */,
      15,    0,   81,    2, 0x08,   14 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QString,    8,    9,   10,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject TestPoints::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSTestPointsENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTestPointsENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTestPointsENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TestPoints, std::true_type>,
        // method 'signal_path'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_pushButton_Confirm_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_lineEdit_count_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refreshTrackerPosition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleTrackerOriginRefreshFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'useTestTrackerPosition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'previewTrackerVisibility'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportPreviewRetainedPoses'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TestPoints::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TestPoints *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signal_path((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->on_pushButton_Confirm_clicked(); break;
        case 2: _t->on_lineEdit_count_editingFinished(); break;
        case 3: _t->refreshTrackerPosition(); break;
        case 4: _t->handleTrackerOriginRefreshFinished((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
        case 5: _t->useTestTrackerPosition(); break;
        case 6: _t->previewTrackerVisibility(); break;
        case 7: _t->exportPreviewRetainedPoses(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TestPoints::*)(QString );
            if (_t _q_method = &TestPoints::signal_path; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *TestPoints::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestPoints::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTestPointsENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int TestPoints::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void TestPoints::signal_path(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
