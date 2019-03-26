/****************************************************************************
** Meta object code from reading C++ file 'hdlc_dlms_exchange.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DLMS_client_waviot-m1_ver.1.01/hdlc_dlms_exchange.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hdlc_dlms_exchange.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HDLC_DLMS_exchange_t {
    QByteArrayData data[15];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HDLC_DLMS_exchange_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HDLC_DLMS_exchange_t qt_meta_stringdata_HDLC_DLMS_exchange = {
    {
QT_MOC_LITERAL(0, 0, 18), // "HDLC_DLMS_exchange"
QT_MOC_LITERAL(1, 19, 21), // "signal_HDLC_to_device"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 4), // "data"
QT_MOC_LITERAL(4, 47, 22), // "signal_PDU_from_device"
QT_MOC_LITERAL(5, 70, 4), // "vpdu"
QT_MOC_LITERAL(6, 75, 12), // "slot_connect"
QT_MOC_LITERAL(7, 88, 8), // "uint32_t"
QT_MOC_LITERAL(8, 97, 6), // "server"
QT_MOC_LITERAL(9, 104, 6), // "client"
QT_MOC_LITERAL(10, 111, 4), // "pass"
QT_MOC_LITERAL(11, 116, 18), // "slot_PDU_to_device"
QT_MOC_LITERAL(12, 135, 21), // "slot_HDLC_from_device"
QT_MOC_LITERAL(13, 157, 38), // "slot_HDLC_MAC_stringify_contr..."
QT_MOC_LITERAL(14, 196, 3) // "pdu"

    },
    "HDLC_DLMS_exchange\0signal_HDLC_to_device\0"
    "\0data\0signal_PDU_from_device\0vpdu\0"
    "slot_connect\0uint32_t\0server\0client\0"
    "pass\0slot_PDU_to_device\0slot_HDLC_from_device\0"
    "slot_HDLC_MAC_stringify_controller_PDU\0"
    "pdu"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HDLC_DLMS_exchange[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,   50,    2, 0x0a /* Public */,
      11,    1,   57,    2, 0x0a /* Public */,
      12,    1,   60,    2, 0x0a /* Public */,
      13,    1,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QVariant,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7, QMetaType::QByteArray,    8,    9,   10,
    QMetaType::Void, QMetaType::QVariant,    5,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QByteArray,   14,

       0        // eod
};

void HDLC_DLMS_exchange::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HDLC_DLMS_exchange *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_HDLC_to_device((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->signal_PDU_from_device((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 2: _t->slot_connect((*reinterpret_cast< uint32_t(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 3: _t->slot_PDU_to_device((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 4: _t->slot_HDLC_from_device((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->slot_HDLC_MAC_stringify_controller_PDU((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HDLC_DLMS_exchange::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HDLC_DLMS_exchange::signal_HDLC_to_device)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HDLC_DLMS_exchange::*)(QVariant );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HDLC_DLMS_exchange::signal_PDU_from_device)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HDLC_DLMS_exchange::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_HDLC_DLMS_exchange.data,
    qt_meta_data_HDLC_DLMS_exchange,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HDLC_DLMS_exchange::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HDLC_DLMS_exchange::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HDLC_DLMS_exchange.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HDLC_DLMS_exchange::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void HDLC_DLMS_exchange::signal_HDLC_to_device(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HDLC_DLMS_exchange::signal_PDU_from_device(QVariant _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
