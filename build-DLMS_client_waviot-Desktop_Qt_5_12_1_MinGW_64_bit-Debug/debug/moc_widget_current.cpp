/****************************************************************************
** Meta object code from reading C++ file 'widget_current.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DLMS_client_waviot-m1/widget_current.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_current.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_model_current_t {
    QByteArrayData data[4];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_model_current_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_model_current_t qt_meta_stringdata_model_current = {
    {
QT_MOC_LITERAL(0, 0, 13), // "model_current"
QT_MOC_LITERAL(1, 14, 17), // "signal_write_data"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 4) // "data"

    },
    "model_current\0signal_write_data\0\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_model_current[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,

       0        // eod
};

void model_current::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<model_current *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_write_data((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (model_current::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&model_current::signal_write_data)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject model_current::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_model_current.data,
    qt_meta_data_model_current,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *model_current::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *model_current::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_model_current.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int model_current::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void model_current::signal_write_data(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_widget_current_t {
    QByteArrayData data[22];
    char stringdata0[463];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_current_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_current_t qt_meta_stringdata_widget_current = {
    {
QT_MOC_LITERAL(0, 0, 14), // "widget_current"
QT_MOC_LITERAL(1, 15, 17), // "signal_write_data"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "data"
QT_MOC_LITERAL(4, 39, 26), // "on_pushButton_EF0A_clicked"
QT_MOC_LITERAL(5, 66, 30), // "on_pushButton_ADE_read_clicked"
QT_MOC_LITERAL(6, 97, 31), // "on_pushButton_ADE_write_clicked"
QT_MOC_LITERAL(7, 129, 34), // "on_pushButton_display_read_cl..."
QT_MOC_LITERAL(8, 164, 35), // "on_pushButton_display_write_c..."
QT_MOC_LITERAL(9, 200, 33), // "on_pushButton_set_Fast_DL_cli..."
QT_MOC_LITERAL(10, 234, 30), // "on_pushButton_set_Time_clicked"
QT_MOC_LITERAL(11, 265, 29), // "on_pushButton_rele_on_clicked"
QT_MOC_LITERAL(12, 295, 30), // "on_pushButton_rele_off_clicked"
QT_MOC_LITERAL(13, 326, 28), // "on_lineEdit_in_returnPressed"
QT_MOC_LITERAL(14, 355, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(15, 377, 29), // "on_lineEdit_out_returnPressed"
QT_MOC_LITERAL(16, 407, 14), // "slot_read_data"
QT_MOC_LITERAL(17, 422, 12), // "slot_connect"
QT_MOC_LITERAL(18, 435, 8), // "uint32_t"
QT_MOC_LITERAL(19, 444, 6), // "server"
QT_MOC_LITERAL(20, 451, 6), // "client"
QT_MOC_LITERAL(21, 458, 4) // "pass"

    },
    "widget_current\0signal_write_data\0\0"
    "data\0on_pushButton_EF0A_clicked\0"
    "on_pushButton_ADE_read_clicked\0"
    "on_pushButton_ADE_write_clicked\0"
    "on_pushButton_display_read_clicked\0"
    "on_pushButton_display_write_clicked\0"
    "on_pushButton_set_Fast_DL_clicked\0"
    "on_pushButton_set_Time_clicked\0"
    "on_pushButton_rele_on_clicked\0"
    "on_pushButton_rele_off_clicked\0"
    "on_lineEdit_in_returnPressed\0"
    "on_pushButton_clicked\0"
    "on_lineEdit_out_returnPressed\0"
    "slot_read_data\0slot_connect\0uint32_t\0"
    "server\0client\0pass"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_current[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   92,    2, 0x08 /* Private */,
       5,    0,   93,    2, 0x08 /* Private */,
       6,    0,   94,    2, 0x08 /* Private */,
       7,    0,   95,    2, 0x08 /* Private */,
       8,    0,   96,    2, 0x08 /* Private */,
       9,    0,   97,    2, 0x08 /* Private */,
      10,    0,   98,    2, 0x08 /* Private */,
      11,    0,   99,    2, 0x08 /* Private */,
      12,    0,  100,    2, 0x08 /* Private */,
      13,    0,  101,    2, 0x08 /* Private */,
      14,    0,  102,    2, 0x08 /* Private */,
      15,    0,  103,    2, 0x08 /* Private */,
      16,    1,  104,    2, 0x0a /* Public */,
      17,    3,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 18, QMetaType::QByteArray,   19,   20,   21,

       0        // eod
};

void widget_current::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget_current *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_write_data((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_EF0A_clicked(); break;
        case 2: _t->on_pushButton_ADE_read_clicked(); break;
        case 3: _t->on_pushButton_ADE_write_clicked(); break;
        case 4: _t->on_pushButton_display_read_clicked(); break;
        case 5: _t->on_pushButton_display_write_clicked(); break;
        case 6: _t->on_pushButton_set_Fast_DL_clicked(); break;
        case 7: _t->on_pushButton_set_Time_clicked(); break;
        case 8: _t->on_pushButton_rele_on_clicked(); break;
        case 9: _t->on_pushButton_rele_off_clicked(); break;
        case 10: _t->on_lineEdit_in_returnPressed(); break;
        case 11: _t->on_pushButton_clicked(); break;
        case 12: _t->on_lineEdit_out_returnPressed(); break;
        case 13: _t->slot_read_data((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 14: _t->slot_connect((*reinterpret_cast< uint32_t(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (widget_current::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_current::signal_write_data)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget_current::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_widget_current.data,
    qt_meta_data_widget_current,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget_current::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget_current::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget_current.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget_current::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void widget_current::signal_write_data(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
