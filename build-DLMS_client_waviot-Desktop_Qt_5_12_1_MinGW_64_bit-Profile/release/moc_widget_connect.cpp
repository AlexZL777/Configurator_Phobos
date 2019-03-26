/****************************************************************************
** Meta object code from reading C++ file 'widget_connect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DLMS_client_waviot-m1/widget_connect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_connect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widget_connect_t {
    QByteArrayData data[23];
    char stringdata0[388];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_connect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_connect_t qt_meta_stringdata_widget_connect = {
    {
QT_MOC_LITERAL(0, 0, 14), // "widget_connect"
QT_MOC_LITERAL(1, 15, 14), // "signal_connect"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 8), // "uint32_t"
QT_MOC_LITERAL(4, 40, 6), // "server"
QT_MOC_LITERAL(5, 47, 6), // "client"
QT_MOC_LITERAL(6, 54, 4), // "pass"
QT_MOC_LITERAL(7, 59, 17), // "signal_disconnect"
QT_MOC_LITERAL(8, 77, 23), // "signal_HDLC_from_device"
QT_MOC_LITERAL(9, 101, 4), // "data"
QT_MOC_LITERAL(10, 106, 16), // "signal_read_data"
QT_MOC_LITERAL(11, 123, 18), // "slot_udp_readyRead"
QT_MOC_LITERAL(12, 142, 21), // "slot_serial_readyRead"
QT_MOC_LITERAL(13, 164, 26), // "slot_update_switch_connect"
QT_MOC_LITERAL(14, 191, 19), // "slot_HDLC_to_device"
QT_MOC_LITERAL(15, 211, 15), // "slot_disconnect"
QT_MOC_LITERAL(16, 227, 29), // "on_pushButton_connect_clicked"
QT_MOC_LITERAL(17, 257, 7), // "checked"
QT_MOC_LITERAL(18, 265, 43), // "on_comboBox_client_addr_curre..."
QT_MOC_LITERAL(19, 309, 5), // "index"
QT_MOC_LITERAL(20, 315, 33), // "on_spinBox_modem_dec_valueCha..."
QT_MOC_LITERAL(21, 349, 4), // "arg1"
QT_MOC_LITERAL(22, 354, 33) // "on_spinBox_modem_hex_valueCha..."

    },
    "widget_connect\0signal_connect\0\0uint32_t\0"
    "server\0client\0pass\0signal_disconnect\0"
    "signal_HDLC_from_device\0data\0"
    "signal_read_data\0slot_udp_readyRead\0"
    "slot_serial_readyRead\0slot_update_switch_connect\0"
    "slot_HDLC_to_device\0slot_disconnect\0"
    "on_pushButton_connect_clicked\0checked\0"
    "on_comboBox_client_addr_currentIndexChanged\0"
    "index\0on_spinBox_modem_dec_valueChanged\0"
    "arg1\0on_spinBox_modem_hex_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_connect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   79,    2, 0x06 /* Public */,
       7,    0,   86,    2, 0x06 /* Public */,
       8,    1,   87,    2, 0x06 /* Public */,
      10,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   93,    2, 0x09 /* Protected */,
      12,    0,   94,    2, 0x09 /* Protected */,
      13,    0,   95,    2, 0x09 /* Protected */,
      14,    1,   96,    2, 0x0a /* Public */,
      15,    0,   99,    2, 0x0a /* Public */,
      16,    1,  100,    2, 0x08 /* Private */,
      18,    1,  103,    2, 0x08 /* Private */,
      20,    1,  106,    2, 0x08 /* Private */,
      22,    1,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::QByteArray,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    9,
    QMetaType::Void, QMetaType::QByteArray,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   21,

       0        // eod
};

void widget_connect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget_connect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_connect((*reinterpret_cast< uint32_t(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 1: _t->signal_disconnect(); break;
        case 2: _t->signal_HDLC_from_device((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->signal_read_data((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->slot_udp_readyRead(); break;
        case 5: _t->slot_serial_readyRead(); break;
        case 6: _t->slot_update_switch_connect(); break;
        case 7: _t->slot_HDLC_to_device((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->slot_disconnect(); break;
        case 9: _t->on_pushButton_connect_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_comboBox_client_addr_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_spinBox_modem_dec_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_spinBox_modem_hex_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (widget_connect::*)(uint32_t , uint32_t , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_connect::signal_connect)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (widget_connect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_connect::signal_disconnect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (widget_connect::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_connect::signal_HDLC_from_device)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (widget_connect::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_connect::signal_read_data)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget_connect::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_widget_connect.data,
    qt_meta_data_widget_connect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget_connect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget_connect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget_connect.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget_connect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void widget_connect::signal_connect(uint32_t _t1, uint32_t _t2, QByteArray _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void widget_connect::signal_disconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void widget_connect::signal_HDLC_from_device(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void widget_connect::signal_read_data(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
