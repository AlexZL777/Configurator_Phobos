/****************************************************************************
** Meta object code from reading C++ file 'widget_power_data.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DLMS_client_waviot-m1_ver.1.01/widget_power_data.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_power_data.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widget_power_data_t {
    QByteArrayData data[9];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_power_data_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_power_data_t qt_meta_stringdata_widget_power_data = {
    {
QT_MOC_LITERAL(0, 0, 17), // "widget_power_data"
QT_MOC_LITERAL(1, 18, 21), // "signal_write_data_PDU"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 14), // "signal_repaint"
QT_MOC_LITERAL(4, 56, 27), // "slot_show_widget_power_data"
QT_MOC_LITERAL(5, 84, 16), // "slot_start_pdata"
QT_MOC_LITERAL(6, 101, 15), // "slot_view_pdata"
QT_MOC_LITERAL(7, 117, 14), // "slot_read_data"
QT_MOC_LITERAL(8, 132, 20) // "slot_hide_power_data"

    },
    "widget_power_data\0signal_write_data_PDU\0"
    "\0signal_repaint\0slot_show_widget_power_data\0"
    "slot_start_pdata\0slot_view_pdata\0"
    "slot_read_data\0slot_hide_power_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_power_data[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    0,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   53,    2, 0x0a /* Public */,
       5,    0,   54,    2, 0x0a /* Public */,
       6,    1,   55,    2, 0x0a /* Public */,
       7,    1,   58,    2, 0x0a /* Public */,
       8,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariant,    2,
    QMetaType::Void, QMetaType::QVariant,    2,
    QMetaType::Void,

       0        // eod
};

void widget_power_data::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget_power_data *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_write_data_PDU((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->signal_repaint(); break;
        case 2: _t->slot_show_widget_power_data(); break;
        case 3: _t->slot_start_pdata(); break;
        case 4: _t->slot_view_pdata((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 5: _t->slot_read_data((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 6: _t->slot_hide_power_data(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (widget_power_data::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_power_data::signal_write_data_PDU)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (widget_power_data::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_power_data::signal_repaint)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget_power_data::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_widget_power_data.data,
    qt_meta_data_widget_power_data,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget_power_data::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget_power_data::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget_power_data.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget_power_data::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void widget_power_data::signal_write_data_PDU(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void widget_power_data::signal_repaint()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
