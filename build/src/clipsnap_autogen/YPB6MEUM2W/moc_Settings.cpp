/****************************************************************************
** Meta object code from reading C++ file 'Settings.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/settings/Settings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Settings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Settings_t {
    const uint offsetsAndSize[40];
    char stringdata0[361];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Settings_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Settings_t qt_meta_stringdata_Settings = {
    {
QT_MOC_LITERAL(0, 8), // "Settings"
QT_MOC_LITERAL(9, 24), // "maxHistoryEntriesChanged"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 20), // "retentionDaysChanged"
QT_MOC_LITERAL(56, 19), // "maxStorageMbChanged"
QT_MOC_LITERAL(76, 23), // "maxPayloadSizeKbChanged"
QT_MOC_LITERAL(100, 21), // "maxImagePixelsChanged"
QT_MOC_LITERAL(122, 22), // "shortcutCaptureChanged"
QT_MOC_LITERAL(145, 22), // "shortcutHistoryChanged"
QT_MOC_LITERAL(168, 24), // "monitoringEnabledChanged"
QT_MOC_LITERAL(193, 23), // "autostartEnabledChanged"
QT_MOC_LITERAL(217, 17), // "maxHistoryEntries"
QT_MOC_LITERAL(235, 13), // "retentionDays"
QT_MOC_LITERAL(249, 12), // "maxStorageMb"
QT_MOC_LITERAL(262, 16), // "maxPayloadSizeKb"
QT_MOC_LITERAL(279, 14), // "maxImagePixels"
QT_MOC_LITERAL(294, 15), // "shortcutCapture"
QT_MOC_LITERAL(310, 15), // "shortcutHistory"
QT_MOC_LITERAL(326, 17), // "monitoringEnabled"
QT_MOC_LITERAL(344, 16) // "autostartEnabled"

    },
    "Settings\0maxHistoryEntriesChanged\0\0"
    "retentionDaysChanged\0maxStorageMbChanged\0"
    "maxPayloadSizeKbChanged\0maxImagePixelsChanged\0"
    "shortcutCaptureChanged\0shortcutHistoryChanged\0"
    "monitoringEnabledChanged\0"
    "autostartEnabledChanged\0maxHistoryEntries\0"
    "retentionDays\0maxStorageMb\0maxPayloadSizeKb\0"
    "maxImagePixels\0shortcutCapture\0"
    "shortcutHistory\0monitoringEnabled\0"
    "autostartEnabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Settings[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       9,   77, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,   10 /* Public */,
       3,    0,   69,    2, 0x06,   11 /* Public */,
       4,    0,   70,    2, 0x06,   12 /* Public */,
       5,    0,   71,    2, 0x06,   13 /* Public */,
       6,    0,   72,    2, 0x06,   14 /* Public */,
       7,    0,   73,    2, 0x06,   15 /* Public */,
       8,    0,   74,    2, 0x06,   16 /* Public */,
       9,    0,   75,    2, 0x06,   17 /* Public */,
      10,    0,   76,    2, 0x06,   18 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      11, QMetaType::Int, 0x00015103, uint(0), 0,
      12, QMetaType::Int, 0x00015103, uint(1), 0,
      13, QMetaType::Int, 0x00015103, uint(2), 0,
      14, QMetaType::Int, 0x00015103, uint(3), 0,
      15, QMetaType::Int, 0x00015103, uint(4), 0,
      16, QMetaType::QString, 0x00015103, uint(5), 0,
      17, QMetaType::QString, 0x00015103, uint(6), 0,
      18, QMetaType::Bool, 0x00015103, uint(7), 0,
      19, QMetaType::Bool, 0x00015103, uint(8), 0,

       0        // eod
};

void Settings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Settings *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->maxHistoryEntriesChanged(); break;
        case 1: _t->retentionDaysChanged(); break;
        case 2: _t->maxStorageMbChanged(); break;
        case 3: _t->maxPayloadSizeKbChanged(); break;
        case 4: _t->maxImagePixelsChanged(); break;
        case 5: _t->shortcutCaptureChanged(); break;
        case 6: _t->shortcutHistoryChanged(); break;
        case 7: _t->monitoringEnabledChanged(); break;
        case 8: _t->autostartEnabledChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Settings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Settings::maxHistoryEntriesChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Settings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Settings::retentionDaysChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Settings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Settings::maxStorageMbChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Settings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Settings::maxPayloadSizeKbChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Settings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Settings::maxImagePixelsChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Settings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Settings::shortcutCaptureChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Settings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Settings::shortcutHistoryChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Settings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Settings::monitoringEnabledChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Settings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Settings::autostartEnabledChanged)) {
                *result = 8;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Settings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->maxHistoryEntries(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->retentionDays(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->maxStorageMb(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->maxPayloadSizeKb(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->maxImagePixels(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->shortcutCapture(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->shortcutHistory(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->monitoringEnabled(); break;
        case 8: *reinterpret_cast< bool*>(_v) = _t->autostartEnabled(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Settings *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMaxHistoryEntries(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setRetentionDays(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setMaxStorageMb(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setMaxPayloadSizeKb(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setMaxImagePixels(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setShortcutCapture(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->setShortcutHistory(*reinterpret_cast< QString*>(_v)); break;
        case 7: _t->setMonitoringEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 8: _t->setAutostartEnabled(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject Settings::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Settings.offsetsAndSize,
    qt_meta_data_Settings,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Settings_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<Settings, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *Settings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Settings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Settings.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Settings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Settings::maxHistoryEntriesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Settings::retentionDaysChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Settings::maxStorageMbChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Settings::maxPayloadSizeKbChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Settings::maxImagePixelsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Settings::shortcutCaptureChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Settings::shortcutHistoryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Settings::monitoringEnabledChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Settings::autostartEnabledChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
