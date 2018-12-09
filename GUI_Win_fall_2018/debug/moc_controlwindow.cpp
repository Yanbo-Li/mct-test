/****************************************************************************
** Meta object code from reading C++ file 'controlwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../controlwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControlWindow_t {
    QByteArrayData data[20];
    char stringdata0[399];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlWindow_t qt_meta_stringdata_ControlWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ControlWindow"
QT_MOC_LITERAL(1, 14, 21), // "on_backButton_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 21), // "on_plotButton_clicked"
QT_MOC_LITERAL(4, 59, 24), // "on_kpMinBox_valueChanged"
QT_MOC_LITERAL(5, 84, 4), // "arg1"
QT_MOC_LITERAL(6, 89, 24), // "on_kdMaxBox_valueChanged"
QT_MOC_LITERAL(7, 114, 24), // "on_kpMaxBox_valueChanged"
QT_MOC_LITERAL(8, 139, 24), // "on_kdMinBox_valueChanged"
QT_MOC_LITERAL(9, 164, 24), // "on_kiMinBox_valueChanged"
QT_MOC_LITERAL(10, 189, 24), // "on_kiMaxBox_valueChanged"
QT_MOC_LITERAL(11, 214, 24), // "on_kpSlider_valueChanged"
QT_MOC_LITERAL(12, 239, 5), // "value"
QT_MOC_LITERAL(13, 245, 24), // "on_kpValBox_valueChanged"
QT_MOC_LITERAL(14, 270, 24), // "on_kdSlider_valueChanged"
QT_MOC_LITERAL(15, 295, 24), // "on_kdValBox_valueChanged"
QT_MOC_LITERAL(16, 320, 24), // "on_kiSlider_valueChanged"
QT_MOC_LITERAL(17, 345, 24), // "on_kiValBox_valueChanged"
QT_MOC_LITERAL(18, 370, 15), // "getClickedPoint"
QT_MOC_LITERAL(19, 386, 12) // "QMouseEvent*"

    },
    "ControlWindow\0on_backButton_clicked\0"
    "\0on_plotButton_clicked\0on_kpMinBox_valueChanged\0"
    "arg1\0on_kdMaxBox_valueChanged\0"
    "on_kpMaxBox_valueChanged\0"
    "on_kdMinBox_valueChanged\0"
    "on_kiMinBox_valueChanged\0"
    "on_kiMaxBox_valueChanged\0"
    "on_kpSlider_valueChanged\0value\0"
    "on_kpValBox_valueChanged\0"
    "on_kdSlider_valueChanged\0"
    "on_kdValBox_valueChanged\0"
    "on_kiSlider_valueChanged\0"
    "on_kiValBox_valueChanged\0getClickedPoint\0"
    "QMouseEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    1,   91,    2, 0x08 /* Private */,
       6,    1,   94,    2, 0x08 /* Private */,
       7,    1,   97,    2, 0x08 /* Private */,
       8,    1,  100,    2, 0x08 /* Private */,
       9,    1,  103,    2, 0x08 /* Private */,
      10,    1,  106,    2, 0x08 /* Private */,
      11,    1,  109,    2, 0x08 /* Private */,
      13,    1,  112,    2, 0x08 /* Private */,
      14,    1,  115,    2, 0x08 /* Private */,
      15,    1,  118,    2, 0x08 /* Private */,
      16,    1,  121,    2, 0x08 /* Private */,
      17,    1,  124,    2, 0x08 /* Private */,
      18,    1,  127,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, 0x80000000 | 19,    2,

       0        // eod
};

void ControlWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ControlWindow *_t = static_cast<ControlWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_backButton_clicked(); break;
        case 1: _t->on_plotButton_clicked(); break;
        case 2: _t->on_kpMinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->on_kdMaxBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->on_kpMaxBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->on_kdMinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->on_kiMinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->on_kiMaxBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->on_kpSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_kpValBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->on_kdSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_kdValBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->on_kiSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_kiValBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->getClickedPoint((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ControlWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControlWindow.data,
      qt_meta_data_ControlWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ControlWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControlWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ControlWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
