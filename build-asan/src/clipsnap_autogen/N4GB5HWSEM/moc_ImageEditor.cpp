/****************************************************************************
** Meta object code from reading C++ file 'ImageEditor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/screenshot/ImageEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageEditor_t {
    const uint offsetsAndSize[60];
    char stringdata0[219];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ImageEditor_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ImageEditor_t qt_meta_stringdata_ImageEditor = {
    {
QT_MOC_LITERAL(0, 11), // "ImageEditor"
QT_MOC_LITERAL(12, 12), // "imageChanged"
QT_MOC_LITERAL(25, 0), // ""
QT_MOC_LITERAL(26, 12), // "editFinished"
QT_MOC_LITERAL(39, 10), // "finalImage"
QT_MOC_LITERAL(50, 12), // "stateChanged"
QT_MOC_LITERAL(63, 8), // "setImage"
QT_MOC_LITERAL(72, 5), // "image"
QT_MOC_LITERAL(78, 4), // "crop"
QT_MOC_LITERAL(83, 14), // "normalizedRect"
QT_MOC_LITERAL(98, 8), // "addArrow"
QT_MOC_LITERAL(107, 2), // "sx"
QT_MOC_LITERAL(110, 2), // "sy"
QT_MOC_LITERAL(113, 2), // "ex"
QT_MOC_LITERAL(116, 2), // "ey"
QT_MOC_LITERAL(119, 8), // "colorHex"
QT_MOC_LITERAL(128, 12), // "addRectangle"
QT_MOC_LITERAL(141, 2), // "nx"
QT_MOC_LITERAL(144, 2), // "ny"
QT_MOC_LITERAL(147, 2), // "nw"
QT_MOC_LITERAL(150, 2), // "nh"
QT_MOC_LITERAL(153, 7), // "addText"
QT_MOC_LITERAL(161, 4), // "text"
QT_MOC_LITERAL(166, 12), // "addRedaction"
QT_MOC_LITERAL(179, 4), // "undo"
QT_MOC_LITERAL(184, 4), // "redo"
QT_MOC_LITERAL(189, 6), // "commit"
QT_MOC_LITERAL(196, 6), // "cancel"
QT_MOC_LITERAL(203, 7), // "canUndo"
QT_MOC_LITERAL(211, 7) // "canRedo"

    },
    "ImageEditor\0imageChanged\0\0editFinished\0"
    "finalImage\0stateChanged\0setImage\0image\0"
    "crop\0normalizedRect\0addArrow\0sx\0sy\0"
    "ex\0ey\0colorHex\0addRectangle\0nx\0ny\0nw\0"
    "nh\0addText\0text\0addRedaction\0undo\0"
    "redo\0commit\0cancel\0canUndo\0canRedo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageEditor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x06,    1 /* Public */,
       3,    1,  105,    2, 0x06,    2 /* Public */,
       5,    0,  108,    2, 0x06,    4 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,  109,    2, 0x02,    5 /* Public */,
       8,    1,  112,    2, 0x02,    7 /* Public */,
      10,    5,  115,    2, 0x02,    9 /* Public */,
      16,    5,  126,    2, 0x02,   15 /* Public */,
      21,    4,  137,    2, 0x02,   21 /* Public */,
      23,    4,  146,    2, 0x02,   26 /* Public */,
      24,    0,  155,    2, 0x02,   31 /* Public */,
      25,    0,  156,    2, 0x02,   32 /* Public */,
      26,    0,  157,    2, 0x02,   33 /* Public */,
      27,    0,  158,    2, 0x02,   34 /* Public */,
      28,    0,  159,    2, 0x102,   35 /* Public | MethodIsConst  */,
      29,    0,  160,    2, 0x102,   36 /* Public | MethodIsConst  */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QImage,    7,
    QMetaType::Void, QMetaType::QRectF,    9,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QString,   11,   12,   13,   14,   15,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QString,   17,   18,   19,   20,   15,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::QString, QMetaType::QString,   17,   18,   22,   15,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   17,   18,   19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,

       0        // eod
};

void ImageEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->imageChanged(); break;
        case 1: _t->editFinished((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 2: _t->stateChanged(); break;
        case 3: _t->setImage((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 4: _t->crop((*reinterpret_cast< std::add_pointer_t<QRectF>>(_a[1]))); break;
        case 5: _t->addArrow((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
        case 6: _t->addRectangle((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
        case 7: _t->addText((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 8: _t->addRedaction((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4]))); break;
        case 9: _t->undo(); break;
        case 10: _t->redo(); break;
        case 11: _t->commit(); break;
        case 12: _t->cancel(); break;
        case 13: { bool _r = _t->canUndo();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->canRedo();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ImageEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageEditor::imageChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ImageEditor::*)(const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageEditor::editFinished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ImageEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageEditor::stateChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ImageEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickImageProvider::staticMetaObject>(),
    qt_meta_stringdata_ImageEditor.offsetsAndSize,
    qt_meta_data_ImageEditor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ImageEditor_t
, QtPrivate::TypeAndForceComplete<ImageEditor, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QRectF &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>

>,
    nullptr
} };


const QMetaObject *ImageEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageEditor.stringdata0))
        return static_cast<void*>(this);
    return QQuickImageProvider::qt_metacast(_clname);
}

int ImageEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickImageProvider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void ImageEditor::imageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ImageEditor::editFinished(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ImageEditor::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
