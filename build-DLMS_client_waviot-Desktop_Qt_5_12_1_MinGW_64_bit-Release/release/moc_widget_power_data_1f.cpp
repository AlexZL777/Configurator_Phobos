/****************************************************************************
** Meta object code from reading C++ file 'widget_power_data_1f.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DLMS_client_waviot-m1_ver.1.01/widget_power_data_1f.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_power_data_1f.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widget_power_data_1f_t {
    QByteArrayData data[8];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_power_data_1f_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_power_data_1f_t qt_meta_stringdata_widget_power_data_1f = {
    {
QT_MOC_LITERAL(0, 0, 20), // "widget_power_data_1f"
QT_MOC_LITERAL(1, 21, 24), // "signal_write_data_PDU_1f"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 30), // "slot_show_widget_power_data_1f"
QT_MOC_LITERAL(4, 78, 23), // "slot_hide_power_data_1f"
QT_MOC_LITERAL(5, 102, 19), // "slot_start_pdata_1f"
QT_MOC_LITERAL(6, 122, 14), // "slot_read_data"
QT_MOC_LITERAL(7, 137, 4) // "data"

    },
    "widget_power_data_1f\0signal_write_data_PDU_1f\0"
    "\0slot_show_widget_power_data_1f\0"
    "slot_hide_power_data_1f\0slot_start_pdata_1f\0"
    "slot_read_data\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_power_data_1f[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   42,    2, 0x0a /* Public */,
       4,    0,   43,    2, 0x0a /* Public */,
       5,    0,   44,    2, 0x0a /* Public */,
       6,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariant,    7,

       0        // eod
};

void widget_power_data_1f::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget_power_data_1f *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_write_data_PDU_1f((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->slot_show_widget_power_data_1f(); break;
        case 2: _t->slot_hide_power_data_1f(); break;
        case 3: _t->slot_start_pdata_1f(); break;
        case 4: _t->slot_read_data((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (widget_power_data_1f::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_power_data_1f::signal_write_data_PDU_1f)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget_power_data_1f::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_widget_power_data_1f.data,
    qt_meta_data_widget_power_data_1f,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget_power_data_1f::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget_power_data_1f::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget_power_data_1f.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget_power_data_1f::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void widget_power_data_1f::signal_write_data_PDU_1f(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
