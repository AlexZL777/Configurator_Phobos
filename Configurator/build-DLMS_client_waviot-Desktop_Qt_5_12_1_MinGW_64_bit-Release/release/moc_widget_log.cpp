/****************************************************************************
** Meta object code from reading C++ file 'widget_log.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Configurator_ver.1.02/DLMS_client_waviot-m1_ver.1.02/widget_log.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_log.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widget_log_t {
    QByteArrayData data[19];
    char stringdata0[323];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_log_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_log_t qt_meta_stringdata_widget_log = {
    {
QT_MOC_LITERAL(0, 0, 10), // "widget_log"
QT_MOC_LITERAL(1, 11, 17), // "signal_write_data"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "signal_bar"
QT_MOC_LITERAL(4, 41, 20), // "signal_timeout_start"
QT_MOC_LITERAL(5, 62, 19), // "signal_timeout_stop"
QT_MOC_LITERAL(6, 82, 21), // "signal_disable_tab_kn"
QT_MOC_LITERAL(7, 104, 36), // "signal_on_pushButton_connect_..."
QT_MOC_LITERAL(8, 141, 13), // "slot_read_log"
QT_MOC_LITERAL(9, 155, 13), // "slot_log_read"
QT_MOC_LITERAL(10, 169, 15), // "slot_disconnect"
QT_MOC_LITERAL(11, 185, 18), // "slot_stop_read_log"
QT_MOC_LITERAL(12, 204, 24), // "slot_log_event_empty_arr"
QT_MOC_LITERAL(13, 229, 13), // "slot_view_log"
QT_MOC_LITERAL(14, 243, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(15, 265, 7), // "timeout"
QT_MOC_LITERAL(16, 273, 16), // "slotRadioToggled"
QT_MOC_LITERAL(17, 290, 13), // "slot_click_bn"
QT_MOC_LITERAL(18, 304, 18) // "slot_click_bn_file"

    },
    "widget_log\0signal_write_data\0\0signal_bar\0"
    "signal_timeout_start\0signal_timeout_stop\0"
    "signal_disable_tab_kn\0"
    "signal_on_pushButton_connect_clicked\0"
    "slot_read_log\0slot_log_read\0slot_disconnect\0"
    "slot_stop_read_log\0slot_log_event_empty_arr\0"
    "slot_view_log\0on_pushButton_clicked\0"
    "timeout\0slotRadioToggled\0slot_click_bn\0"
    "slot_click_bn_file"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_log[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       3,    1,  102,    2, 0x06 /* Public */,
       4,    1,  105,    2, 0x06 /* Public */,
       5,    0,  108,    2, 0x06 /* Public */,
       6,    2,  109,    2, 0x06 /* Public */,
       7,    1,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  117,    2, 0x0a /* Public */,
       9,    1,  118,    2, 0x0a /* Public */,
      10,    0,  121,    2, 0x0a /* Public */,
      11,    0,  122,    2, 0x0a /* Public */,
      12,    0,  123,    2, 0x0a /* Public */,
      13,    0,  124,    2, 0x0a /* Public */,
      14,    0,  125,    2, 0x08 /* Private */,
      15,    0,  126,    2, 0x08 /* Private */,
      16,    1,  127,    2, 0x08 /* Private */,
      17,    0,  130,    2, 0x08 /* Private */,
      18,    0,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void widget_log::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget_log *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_write_data((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->signal_bar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signal_timeout_start((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signal_timeout_stop(); break;
        case 4: _t->signal_disable_tab_kn((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->signal_on_pushButton_connect_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->slot_read_log(); break;
        case 7: _t->slot_log_read((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->slot_disconnect(); break;
        case 9: _t->slot_stop_read_log(); break;
        case 10: _t->slot_log_event_empty_arr(); break;
        case 11: _t->slot_view_log(); break;
        case 12: _t->on_pushButton_clicked(); break;
        case 13: _t->timeout(); break;
        case 14: _t->slotRadioToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->slot_click_bn(); break;
        case 16: _t->slot_click_bn_file(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (widget_log::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log::signal_write_data)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (widget_log::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log::signal_bar)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (widget_log::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log::signal_timeout_start)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (widget_log::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log::signal_timeout_stop)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (widget_log::*)(bool , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log::signal_disable_tab_kn)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (widget_log::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log::signal_on_pushButton_connect_clicked)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget_log::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_widget_log.data,
    qt_meta_data_widget_log,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget_log::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget_log::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget_log.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget_log::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void widget_log::signal_write_data(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void widget_log::signal_bar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void widget_log::signal_timeout_start(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void widget_log::signal_timeout_stop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void widget_log::signal_disable_tab_kn(bool _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void widget_log::signal_on_pushButton_connect_clicked(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
struct qt_meta_stringdata_TModel_log_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TModel_log_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TModel_log_t qt_meta_stringdata_TModel_log = {
    {
QT_MOC_LITERAL(0, 0, 10) // "TModel_log"

    },
    "TModel_log"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TModel_log[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void TModel_log::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TModel_log::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_TModel_log.data,
    qt_meta_data_TModel_log,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TModel_log::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TModel_log::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TModel_log.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int TModel_log::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
