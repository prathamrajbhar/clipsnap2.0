/****************************************************************************
** Meta object code from reading C++ file 'GnomeClipboardBackend.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/clipboard/GnomeClipboardBackend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GnomeClipboardBackend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GnomeClipboardBackend_t {
    const uint offsetsAndSize[20];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GnomeClipboardBackend_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GnomeClipboardBackend_t qt_meta_stringdata_GnomeClipboardBackend = {
    {
QT_MOC_LITERAL(0, 21), // "GnomeClipboardBackend"
QT_MOC_LITERAL(22, 15), // "D-Bus Interface"
QT_MOC_LITERAL(38, 21), // "app.clipsnap.Monitor1"
QT_MOC_LITERAL(60, 16), // "ClipboardChanged"
QT_MOC_LITERAL(77, 9), // "Q_NOREPLY"
QT_MOC_LITERAL(87, 12), // "content_type"
QT_MOC_LITERAL(100, 4), // "data"
QT_MOC_LITERAL(105, 4), // "Ping"
QT_MOC_LITERAL(110, 0), // ""
QT_MOC_LITERAL(111, 16) // "MonitoringActive"

    },
    "GnomeClipboardBackend\0D-Bus Interface\0"
    "app.clipsnap.Monitor1\0ClipboardChanged\0"
    "Q_NOREPLY\0content_type\0data\0Ping\0\0"
    "MonitoringActive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GnomeClipboardBackend[] = {

 // content:
      10,       // revision
       0,       // classname
       1,   14, // classinfo
       2,   16, // methods
       1,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    2,   28,    4, 0x0a,    2 /* Public */,
       7,    0,   33,    8, 0x0a,    5 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void,

 // properties: name, type, flags
       9, QMetaType::Bool, 0x00015001, uint(-1), 0,

       0        // eod
};

void GnomeClipboardBackend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GnomeClipboardBackend *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ClipboardChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->Ping(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GnomeClipboardBackend *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isMonitoring(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject GnomeClipboardBackend::staticMetaObject = { {
    QMetaObject::SuperData::link<ClipboardBackend::staticMetaObject>(),
    qt_meta_stringdata_GnomeClipboardBackend.offsetsAndSize,
    qt_meta_data_GnomeClipboardBackend,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GnomeClipboardBackend_t
, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<GnomeClipboardBackend, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *GnomeClipboardBackend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GnomeClipboardBackend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GnomeClipboardBackend.stringdata0))
        return static_cast<void*>(this);
    return ClipboardBackend::qt_metacast(_clname);
}

int GnomeClipboardBackend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ClipboardBackend::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
