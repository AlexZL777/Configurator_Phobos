/****************************************************************************
** Meta object code from reading C++ file 'widget_pulse_outputs.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DLMS_client_waviot-m1_ver.1.01/widget_pulse_outputs.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_pulse_outputs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widget_pulse_outputs_t {
    QByteArrayData data[14];
    char stringdata0[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_pulse_outputs_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_pulse_outputs_t qt_meta_stringdata_widget_pulse_outputs = {
    {
QT_MOC_LITERAL(0, 0, 20), // "widget_pulse_outputs"
QT_MOC_LITERAL(1, 21, 18), // "signal_write_data_"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 4), // "data"
QT_MOC_LITERAL(4, 46, 21), // "signal_updateGeometry"
QT_MOC_LITERAL(5, 68, 17), // "signal_min_window"
QT_MOC_LITERAL(6, 86, 18), // "signal_start_pdata"
QT_MOC_LITERAL(7, 105, 21), // "signal_start_pdata_1f"
QT_MOC_LITERAL(8, 127, 10), // "signal_bar"
QT_MOC_LITERAL(9, 138, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(10, 160, 15), // "slot_read_data_"
QT_MOC_LITERAL(11, 176, 22), // "slot_show_widget_pulse"
QT_MOC_LITERAL(12, 199, 22), // "slot_hide_widget_pulse"
QT_MOC_LITERAL(13, 222, 16) // "slot_start_pulse"

    },
    "widget_pulse_outputs\0signal_write_data_\0"
    "\0data\0signal_updateGeometry\0"
    "signal_min_window\0signal_start_pdata\0"
    "signal_start_pdata_1f\0signal_bar\0"
    "on_pushButton_clicked\0slot_read_data_\0"
    "slot_show_widget_pulse\0slot_hide_widget_pulse\0"
    "slot_start_pulse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_pulse_outputs[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    0,   72,    2, 0x06 /* Public */,
       5,    0,   73,    2, 0x06 /* Public */,
       6,    0,   74,    2, 0x06 /* Public */,
       7,    0,   75,    2, 0x06 /* Public */,
       8,    1,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   79,    2, 0x08 /* Private */,
      10,    1,   80,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    0,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void widget_pulse_outputs::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget_pulse_outputs *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_write_data_((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->signal_updateGeometry(); break;
        case 2: _t->signal_min_window(); break;
        case 3: _t->signal_start_pdata(); break;
        case 4: _t->signal_start_pdata_1f(); break;
        case 5: _t->signal_bar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_clicked(); break;
        case 7: _t->slot_read_data_((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->slot_show_widget_pulse(); break;
        case 9: _t->slot_hide_widget_pulse(); break;
        case 10: _t->slot_start_pulse(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (widget_pulse_outputs::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_pulse_outputs::signal_write_data_)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (widget_pulse_outputs::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_pulse_outputs::signal_updateGeometry)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (widget_pulse_outputs::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_pulse_outputs::signal_min_window)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (widget_pulse_outputs::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_pulse_outputs::signal_start_pdata)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (widget_pulse_outputs::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_pulse_outputs::signal_start_pdata_1f)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (widget_pulse_outputs::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_pulse_outputs::signal_bar)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget_pulse_outputs::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_widget_pulse_outputs.data,
    qt_meta_data_widget_pulse_outputs,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget_pulse_outputs::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget_pulse_outputs::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget_pulse_outputs.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget_pulse_outputs::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void widget_pulse_outputs::signal_write_data_(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void widget_pulse_outputs::signal_updateGeometry()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void widget_pulse_outputs::signal_min_window()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void widget_pulse_outputs::signal_start_pdata()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void widget_pulse_outputs::signal_start_pdata_1f()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void widget_pulse_outputs::signal_bar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
