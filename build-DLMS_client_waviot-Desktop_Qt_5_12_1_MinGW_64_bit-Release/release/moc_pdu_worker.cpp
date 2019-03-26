/****************************************************************************
** Meta object code from reading C++ file 'pdu_worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DLMS_client_waviot-m1_ver.1.01/pdu_worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pdu_worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_pdu_worker_t {
    QByteArrayData data[21];
    char stringdata0[306];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pdu_worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pdu_worker_t qt_meta_stringdata_pdu_worker = {
    {
QT_MOC_LITERAL(0, 0, 10), // "pdu_worker"
QT_MOC_LITERAL(1, 11, 20), // "signal_PDU_to_device"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 4), // "vpdu"
QT_MOC_LITERAL(4, 38, 27), // "signal_electro5_from_device"
QT_MOC_LITERAL(5, 66, 3), // "arr"
QT_MOC_LITERAL(6, 70, 11), // "signal_data"
QT_MOC_LITERAL(7, 82, 34), // "signal_get_respons_with_data_..."
QT_MOC_LITERAL(8, 117, 23), // "signal_show_widget_info"
QT_MOC_LITERAL(9, 141, 24), // "signal_show_widget_pulse"
QT_MOC_LITERAL(10, 166, 10), // "signal_bar"
QT_MOC_LITERAL(11, 177, 4), // "data"
QT_MOC_LITERAL(12, 182, 17), // "signal_write_pass"
QT_MOC_LITERAL(13, 200, 4), // "pass"
QT_MOC_LITERAL(14, 205, 17), // "signal_error_pass"
QT_MOC_LITERAL(15, 223, 20), // "slot_PDU_from_device"
QT_MOC_LITERAL(16, 244, 23), // "slot_electro5_to_device"
QT_MOC_LITERAL(17, 268, 14), // "slot_test_pass"
QT_MOC_LITERAL(18, 283, 8), // "uint32_t"
QT_MOC_LITERAL(19, 292, 6), // "server"
QT_MOC_LITERAL(20, 299, 6) // "client"

    },
    "pdu_worker\0signal_PDU_to_device\0\0vpdu\0"
    "signal_electro5_from_device\0arr\0"
    "signal_data\0signal_get_respons_with_data_block\0"
    "signal_show_widget_info\0"
    "signal_show_widget_pulse\0signal_bar\0"
    "data\0signal_write_pass\0pass\0"
    "signal_error_pass\0slot_PDU_from_device\0"
    "slot_electro5_to_device\0slot_test_pass\0"
    "uint32_t\0server\0client"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pdu_worker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       6,    1,   80,    2, 0x06 /* Public */,
       7,    3,   83,    2, 0x06 /* Public */,
       8,    0,   90,    2, 0x06 /* Public */,
       9,    0,   91,    2, 0x06 /* Public */,
      10,    1,   92,    2, 0x06 /* Public */,
      12,    2,   95,    2, 0x06 /* Public */,
      14,    0,  100,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    1,  101,    2, 0x0a /* Public */,
      16,    1,  104,    2, 0x0a /* Public */,
      17,    3,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVariant,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QVariant,    5,
    QMetaType::Void, QMetaType::QVariant, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Bool,   13,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QVariant,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 18, QMetaType::QByteArray,   19,   20,   13,

       0        // eod
};

void pdu_worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<pdu_worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_PDU_to_device((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: _t->signal_electro5_from_device((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->signal_data((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 3: _t->signal_get_respons_with_data_block((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->signal_show_widget_info(); break;
        case 5: _t->signal_show_widget_pulse(); break;
        case 6: _t->signal_bar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->signal_write_pass((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->signal_error_pass(); break;
        case 9: _t->slot_PDU_from_device((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 10: _t->slot_electro5_to_device((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 11: _t->slot_test_pass((*reinterpret_cast< uint32_t(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (pdu_worker::*)(QVariant );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pdu_worker::signal_PDU_to_device)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (pdu_worker::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pdu_worker::signal_electro5_from_device)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (pdu_worker::*)(QVariant );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pdu_worker::signal_data)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (pdu_worker::*)(QVariant , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pdu_worker::signal_get_respons_with_data_block)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (pdu_worker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pdu_worker::signal_show_widget_info)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (pdu_worker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pdu_worker::signal_show_widget_pulse)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (pdu_worker::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pdu_worker::signal_bar)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (pdu_worker::*)(QByteArray , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pdu_worker::signal_write_pass)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (pdu_worker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pdu_worker::signal_error_pass)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject pdu_worker::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_pdu_worker.data,
    qt_meta_data_pdu_worker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *pdu_worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pdu_worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_pdu_worker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int pdu_worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void pdu_worker::signal_PDU_to_device(QVariant _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void pdu_worker::signal_electro5_from_device(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void pdu_worker::signal_data(QVariant _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void pdu_worker::signal_get_respons_with_data_block(QVariant _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void pdu_worker::signal_show_widget_info()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void pdu_worker::signal_show_widget_pulse()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void pdu_worker::signal_bar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void pdu_worker::signal_write_pass(QByteArray _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void pdu_worker::signal_error_pass()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
