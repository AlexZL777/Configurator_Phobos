/****************************************************************************
** Meta object code from reading C++ file 'widget_info.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DLMS_client_waviot-m1_ver.1.01/widget_info.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_info.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widget_info_t {
    QByteArrayData data[13];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_info_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_info_t qt_meta_stringdata_widget_info = {
    {
QT_MOC_LITERAL(0, 0, 11), // "widget_info"
QT_MOC_LITERAL(1, 12, 21), // "signal_write_data_PDU"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 4), // "data"
QT_MOC_LITERAL(4, 40, 18), // "signal_start_pulse"
QT_MOC_LITERAL(5, 59, 10), // "signal_bar"
QT_MOC_LITERAL(6, 70, 17), // "signal_min_window"
QT_MOC_LITERAL(7, 88, 29), // "signal_show_widget_power_data"
QT_MOC_LITERAL(8, 118, 32), // "signal_show_widget_power_data_1f"
QT_MOC_LITERAL(9, 151, 23), // "signal_show_point_power"
QT_MOC_LITERAL(10, 175, 14), // "slot_view_data"
QT_MOC_LITERAL(11, 190, 21), // "slot_show_widget_info"
QT_MOC_LITERAL(12, 212, 21) // "slot_hide_widget_info"

    },
    "widget_info\0signal_write_data_PDU\0\0"
    "data\0signal_start_pulse\0signal_bar\0"
    "signal_min_window\0signal_show_widget_power_data\0"
    "signal_show_widget_power_data_1f\0"
    "signal_show_point_power\0slot_view_data\0"
    "slot_show_widget_info\0slot_hide_widget_info"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_info[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    0,   67,    2, 0x06 /* Public */,
       5,    1,   68,    2, 0x06 /* Public */,
       6,    0,   71,    2, 0x06 /* Public */,
       7,    0,   72,    2, 0x06 /* Public */,
       8,    0,   73,    2, 0x06 /* Public */,
       9,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   75,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QVariant,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void widget_info::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget_info *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_write_data_PDU((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->signal_start_pulse(); break;
        case 2: _t->signal_bar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signal_min_window(); break;
        case 4: _t->signal_show_widget_power_data(); break;
        case 5: _t->signal_show_widget_power_data_1f(); break;
        case 6: _t->signal_show_point_power(); break;
        case 7: _t->slot_view_data((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 8: _t->slot_show_widget_info(); break;
        case 9: _t->slot_hide_widget_info(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (widget_info::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_info::signal_write_data_PDU)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (widget_info::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_info::signal_start_pulse)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (widget_info::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_info::signal_bar)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (widget_info::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_info::signal_min_window)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (widget_info::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_info::signal_show_widget_power_data)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (widget_info::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_info::signal_show_widget_power_data_1f)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (widget_info::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_info::signal_show_point_power)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget_info::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_widget_info.data,
    qt_meta_data_widget_info,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget_info::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget_info::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget_info.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget_info::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void widget_info::signal_write_data_PDU(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void widget_info::signal_start_pulse()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void widget_info::signal_bar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void widget_info::signal_min_window()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void widget_info::signal_show_widget_power_data()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void widget_info::signal_show_widget_power_data_1f()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void widget_info::signal_show_point_power()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
