/****************************************************************************
** Meta object code from reading C++ file 'widget_power_data.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Configurator_ver.1.02/DLMS_client_waviot-m1_ver.1.02/widget_power_data.h"
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
    QByteArrayData data[15];
    char stringdata0[257];
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
QT_MOC_LITERAL(4, 56, 10), // "signal_bar"
QT_MOC_LITERAL(5, 67, 4), // "data"
QT_MOC_LITERAL(6, 72, 20), // "signal_timeout_start"
QT_MOC_LITERAL(7, 93, 21), // "signal_disable_tab_kn"
QT_MOC_LITERAL(8, 115, 36), // "signal_on_pushButton_connect_..."
QT_MOC_LITERAL(9, 152, 15), // "slot_disconnect"
QT_MOC_LITERAL(10, 168, 27), // "slot_show_widget_power_data"
QT_MOC_LITERAL(11, 196, 16), // "slot_start_pdata"
QT_MOC_LITERAL(12, 213, 14), // "slot_read_data"
QT_MOC_LITERAL(13, 228, 20), // "slot_hide_power_data"
QT_MOC_LITERAL(14, 249, 7) // "timeout"

    },
    "widget_power_data\0signal_write_data_PDU\0"
    "\0signal_repaint\0signal_bar\0data\0"
    "signal_timeout_start\0signal_disable_tab_kn\0"
    "signal_on_pushButton_connect_clicked\0"
    "slot_disconnect\0slot_show_widget_power_data\0"
    "slot_start_pdata\0slot_read_data\0"
    "slot_hide_power_data\0timeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_power_data[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       3,    0,   77,    2, 0x06 /* Public */,
       4,    1,   78,    2, 0x06 /* Public */,
       6,    1,   81,    2, 0x06 /* Public */,
       7,    2,   84,    2, 0x06 /* Public */,
       8,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   92,    2, 0x0a /* Public */,
      10,    0,   93,    2, 0x0a /* Public */,
      11,    0,   94,    2, 0x0a /* Public */,
      12,    1,   95,    2, 0x0a /* Public */,
      13,    0,   98,    2, 0x0a /* Public */,
      14,    0,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariant,    2,
    QMetaType::Void,
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
        case 2: _t->signal_bar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signal_timeout_start((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signal_disable_tab_kn((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->signal_on_pushButton_connect_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->slot_disconnect(); break;
        case 7: _t->slot_show_widget_power_data(); break;
        case 8: _t->slot_start_pdata(); break;
        case 9: _t->slot_read_data((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 10: _t->slot_hide_power_data(); break;
        case 11: _t->timeout(); break;
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
        {
            using _t = void (widget_power_data::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_power_data::signal_bar)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (widget_power_data::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_power_data::signal_timeout_start)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (widget_power_data::*)(bool , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_power_data::signal_disable_tab_kn)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (widget_power_data::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_power_data::signal_on_pushButton_connect_clicked)) {
                *result = 5;
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

// SIGNAL 2
void widget_power_data::signal_bar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void widget_power_data::signal_timeout_start(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void widget_power_data::signal_disable_tab_kn(bool _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void widget_power_data::signal_on_pushButton_connect_clicked(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
