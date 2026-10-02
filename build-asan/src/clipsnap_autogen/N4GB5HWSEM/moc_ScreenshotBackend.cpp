/****************************************************************************
** Meta object code from reading C++ file 'ScreenshotBackend.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/screenshot/ScreenshotBackend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScreenshotBackend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScreenshotBackend_t {
    const uint offsetsAndSize[28];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ScreenshotBackend_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ScreenshotBackend_t qt_meta_stringdata_ScreenshotBackend = {
    {
QT_MOC_LITERAL(0, 17), // "ScreenshotBackend"
QT_MOC_LITERAL(18, 15), // "captureComplete"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 5), // "image"
QT_MOC_LITERAL(41, 14), // "capturedRegion"
QT_MOC_LITERAL(56, 16), // "captureCancelled"
QT_MOC_LITERAL(73, 23), // "capturePermissionDenied"
QT_MOC_LITERAL(97, 18), // "captureUnsupported"
QT_MOC_LITERAL(116, 6), // "reason"
QT_MOC_LITERAL(123, 12), // "captureError"
QT_MOC_LITERAL(136, 7), // "message"
QT_MOC_LITERAL(144, 12), // "startCapture"
QT_MOC_LITERAL(157, 11), // "backendName"
QT_MOC_LITERAL(169, 20) // "supportsNativeRegion"

    },
    "ScreenshotBackend\0captureComplete\0\0"
    "image\0capturedRegion\0captureCancelled\0"
    "capturePermissionDenied\0captureUnsupported\0"
    "reason\0captureError\0message\0startCapture\0"
    "backendName\0supportsNativeRegion"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScreenshotBackend[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   62,    2, 0x06,    1 /* Public */,
       5,    0,   67,    2, 0x06,    4 /* Public */,
       6,    0,   68,    2, 0x06,    5 /* Public */,
       7,    1,   69,    2, 0x06,    6 /* Public */,
       9,    1,   72,    2, 0x06,    8 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      11,    0,   75,    2, 0x02,   10 /* Public */,
      12,    0,   76,    2, 0x102,   11 /* Public | MethodIsConst  */,
      13,    0,   77,    2, 0x102,   12 /* Public | MethodIsConst  */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage, QMetaType::QRect,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,

 // methods: parameters
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Bool,

       0        // eod
};

void ScreenshotBackend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScreenshotBackend *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->captureComplete((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QRect>>(_a[2]))); break;
        case 1: _t->captureCancelled(); break;
        case 2: _t->capturePermissionDenied(); break;
        case 3: _t->captureUnsupported((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->captureError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->startCapture(); break;
        case 6: { QString _r = _t->backendName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->supportsNativeRegion();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ScreenshotBackend::*)(QImage , QRect );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScreenshotBackend::captureComplete)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ScreenshotBackend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScreenshotBackend::captureCancelled)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ScreenshotBackend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScreenshotBackend::capturePermissionDenied)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ScreenshotBackend::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScreenshotBackend::captureUnsupported)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ScreenshotBackend::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScreenshotBackend::captureError)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject ScreenshotBackend::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ScreenshotBackend.offsetsAndSize,
    qt_meta_data_ScreenshotBackend,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ScreenshotBackend_t
, QtPrivate::TypeAndForceComplete<ScreenshotBackend, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QImage, std::false_type>, QtPrivate::TypeAndForceComplete<QRect, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>

>,
    nullptr
} };


const QMetaObject *ScreenshotBackend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScreenshotBackend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenshotBackend.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ScreenshotBackend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void ScreenshotBackend::captureComplete(QImage _t1, QRect _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScreenshotBackend::captureCancelled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ScreenshotBackend::capturePermissionDenied()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ScreenshotBackend::captureUnsupported(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ScreenshotBackend::captureError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
