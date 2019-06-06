/****************************************************************************
** Meta object code from reading C++ file 'widget_pdu_worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Configurator_ver.1.02/DLMS_client_waviot-m1_ver.1.02/widget_pdu_worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_pdu_worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widget_PDU_worker_t {
    QByteArrayData data[10];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_PDU_worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_PDU_worker_t qt_meta_stringdata_widget_PDU_worker = {
    {
QT_MOC_LITERAL(0, 0, 17), // "widget_PDU_worker"
QT_MOC_LITERAL(1, 18, 20), // "signal_PDU_to_device"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 4), // "vpdu"
QT_MOC_LITERAL(4, 45, 27), // "signal_electro5_from_device"
QT_MOC_LITERAL(5, 73, 3), // "arr"
QT_MOC_LITERAL(6, 77, 20), // "slot_PDU_from_device"
QT_MOC_LITERAL(7, 98, 23), // "slot_electro5_to_device"
QT_MOC_LITERAL(8, 122, 24), // "on_pushButton_fw_clicked"
QT_MOC_LITERAL(9, 147, 34) // "on_pushButton_electro_spec_cl..."

    },
    "widget_PDU_worker\0signal_PDU_to_device\0"
    "\0vpdu\0signal_electro5_from_device\0arr\0"
    "slot_PDU_from_device\0slot_electro5_to_device\0"
    "on_pushButton_fw_clicked\0"
    "on_pushButton_electro_spec_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_PDU_worker[] = {

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
       6,    1,   50,    2, 0x0a /* Public */,
       7,    1,   53,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVariant,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QVariant,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void widget_PDU_worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget_PDU_worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_PDU_to_device((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: _t->signal_electro5_from_device((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->slot_PDU_from_device((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 3: _t->slot_electro5_to_device((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_fw_clicked(); break;
        case 5: _t->on_pushButton_electro_spec_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (widget_PDU_worker::*)(QVariant );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_PDU_worker::signal_PDU_to_device)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (widget_PDU_worker::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_PDU_worker::signal_electro5_from_device)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget_PDU_worker::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_widget_PDU_worker.data,
    qt_meta_data_widget_PDU_worker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget_PDU_worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget_PDU_worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget_PDU_worker.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget_PDU_worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void widget_PDU_worker::signal_PDU_to_device(QVariant _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void widget_PDU_worker::signal_electro5_from_device(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
