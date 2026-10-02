/****************************************************************************
** Meta object code from reading C++ file 'AppController.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/ui/AppController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AppController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AppController_t {
    const uint offsetsAndSize[20];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_AppController_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_AppController_t qt_meta_stringdata_AppController = {
    {
QT_MOC_LITERAL(0, 13), // "AppController"
QT_MOC_LITERAL(14, 23), // "monitoringActiveChanged"
QT_MOC_LITERAL(38, 0), // ""
QT_MOC_LITERAL(39, 16), // "historyRequested"
QT_MOC_LITERAL(56, 16), // "captureRequested"
QT_MOC_LITERAL(73, 17), // "settingsRequested"
QT_MOC_LITERAL(91, 12), // "openSettings"
QT_MOC_LITERAL(104, 15), // "pauseMonitoring"
QT_MOC_LITERAL(120, 16), // "resumeMonitoring"
QT_MOC_LITERAL(137, 16) // "monitoringActive"

    },
    "AppController\0monitoringActiveChanged\0"
    "\0historyRequested\0captureRequested\0"
    "settingsRequested\0openSettings\0"
    "pauseMonitoring\0resumeMonitoring\0"
    "monitoringActive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AppController[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       1,   63, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    2 /* Public */,
       3,    0,   57,    2, 0x06,    3 /* Public */,
       4,    0,   58,    2, 0x06,    4 /* Public */,
       5,    0,   59,    2, 0x06,    5 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   60,    2, 0x02,    6 /* Public */,
       7,    0,   61,    2, 0x02,    7 /* Public */,
       8,    0,   62,    2, 0x02,    8 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       9, QMetaType::Bool, 0x00015001, uint(0), 0,

       0        // eod
};

void AppController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AppController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->monitoringActiveChanged(); break;
        case 1: _t->historyRequested(); break;
        case 2: _t->captureRequested(); break;
        case 3: _t->settingsRequested(); break;
        case 4: _t->openSettings(); break;
        case 5: _t->pauseMonitoring(); break;
        case 6: _t->resumeMonitoring(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AppController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppController::monitoringActiveChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AppController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppController::historyRequested)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AppController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppController::captureRequested)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AppController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppController::settingsRequested)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AppController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->monitoringActive(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject AppController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AppController.offsetsAndSize,
    qt_meta_data_AppController,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_AppController_t
, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<AppController, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

>,
    nullptr
} };


const QMetaObject *AppController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AppController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AppController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AppController::monitoringActiveChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AppController::historyRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AppController::captureRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AppController::settingsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
