/****************************************************************************
** Meta object code from reading C++ file 'CropRegionSelector.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/screenshot/CropRegionSelector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CropRegionSelector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CropRegionSelector_t {
    const uint offsetsAndSize[36];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_CropRegionSelector_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_CropRegionSelector_t qt_meta_stringdata_CropRegionSelector = {
    {
QT_MOC_LITERAL(0, 18), // "CropRegionSelector"
QT_MOC_LITERAL(19, 13), // "cropConfirmed"
QT_MOC_LITERAL(33, 0), // ""
QT_MOC_LITERAL(34, 12), // "croppedImage"
QT_MOC_LITERAL(47, 13), // "cropCancelled"
QT_MOC_LITERAL(61, 18), // "sourceImageChanged"
QT_MOC_LITERAL(80, 16), // "selectionChanged"
QT_MOC_LITERAL(97, 11), // "confirmCrop"
QT_MOC_LITERAL(109, 6), // "cancel"
QT_MOC_LITERAL(116, 13), // "normalizeRect"
QT_MOC_LITERAL(130, 2), // "x1"
QT_MOC_LITERAL(133, 2), // "y1"
QT_MOC_LITERAL(136, 2), // "x2"
QT_MOC_LITERAL(139, 2), // "y2"
QT_MOC_LITERAL(142, 11), // "sourceImage"
QT_MOC_LITERAL(154, 9), // "selection"
QT_MOC_LITERAL(164, 10), // "imageWidth"
QT_MOC_LITERAL(175, 11) // "imageHeight"

    },
    "CropRegionSelector\0cropConfirmed\0\0"
    "croppedImage\0cropCancelled\0"
    "sourceImageChanged\0selectionChanged\0"
    "confirmCrop\0cancel\0normalizeRect\0x1\0"
    "y1\0x2\0y2\0sourceImage\0selection\0"
    "imageWidth\0imageHeight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CropRegionSelector[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       4,   73, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    5 /* Public */,
       4,    0,   59,    2, 0x06,    7 /* Public */,
       5,    0,   60,    2, 0x06,    8 /* Public */,
       6,    0,   61,    2, 0x06,    9 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   62,    2, 0x02,   10 /* Public */,
       8,    0,   63,    2, 0x02,   11 /* Public */,
       9,    4,   64,    2, 0x102,   12 /* Public | MethodIsConst  */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QRectF, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal,   10,   11,   12,   13,

 // properties: name, type, flags
      14, QMetaType::QImage, 0x00015103, uint(2), 0,
      15, QMetaType::QRectF, 0x00015103, uint(3), 0,
      16, QMetaType::Int, 0x00015001, uint(2), 0,
      17, QMetaType::Int, 0x00015001, uint(2), 0,

       0        // eod
};

void CropRegionSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CropRegionSelector *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->cropConfirmed((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 1: _t->cropCancelled(); break;
        case 2: _t->sourceImageChanged(); break;
        case 3: _t->selectionChanged(); break;
        case 4: _t->confirmCrop(); break;
        case 5: _t->cancel(); break;
        case 6: { QRectF _r = _t->normalizeRect((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[4])));
            if (_a[0]) *reinterpret_cast< QRectF*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CropRegionSelector::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CropRegionSelector::cropConfirmed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CropRegionSelector::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CropRegionSelector::cropCancelled)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CropRegionSelector::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CropRegionSelector::sourceImageChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CropRegionSelector::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CropRegionSelector::selectionChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CropRegionSelector *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QImage*>(_v) = _t->sourceImage(); break;
        case 1: *reinterpret_cast< QRectF*>(_v) = _t->selection(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->imageWidth(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->imageHeight(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CropRegionSelector *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSourceImage(*reinterpret_cast< QImage*>(_v)); break;
        case 1: _t->setSelection(*reinterpret_cast< QRectF*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject CropRegionSelector::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CropRegionSelector.offsetsAndSize,
    qt_meta_data_CropRegionSelector,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_CropRegionSelector_t
, QtPrivate::TypeAndForceComplete<QImage, std::true_type>, QtPrivate::TypeAndForceComplete<QRectF, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<CropRegionSelector, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QImage, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QRectF, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>

>,
    nullptr
} };


const QMetaObject *CropRegionSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CropRegionSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CropRegionSelector.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CropRegionSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CropRegionSelector::cropConfirmed(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CropRegionSelector::cropCancelled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CropRegionSelector::sourceImageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CropRegionSelector::selectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
