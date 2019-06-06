/****************************************************************************
** Meta object code from reading C++ file 'widget_log_event.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Configurator_ver.1.02/DLMS_client_waviot-m1_ver.1.02/widget_log_event.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_log_event.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widget_log_event_t {
    QByteArrayData data[17];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_log_event_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_log_event_t qt_meta_stringdata_widget_log_event = {
    {
QT_MOC_LITERAL(0, 0, 16), // "widget_log_event"
QT_MOC_LITERAL(1, 17, 17), // "signal_write_data"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 10), // "signal_bar"
QT_MOC_LITERAL(4, 47, 20), // "signal_timeout_start"
QT_MOC_LITERAL(5, 68, 19), // "signal_timeout_stop"
QT_MOC_LITERAL(6, 88, 21), // "signal_disable_tab_kn"
QT_MOC_LITERAL(7, 110, 36), // "signal_on_pushButton_connect_..."
QT_MOC_LITERAL(8, 147, 7), // "timeout"
QT_MOC_LITERAL(9, 155, 16), // "slotRadioToggled"
QT_MOC_LITERAL(10, 172, 9), // "slotCombo"
QT_MOC_LITERAL(11, 182, 19), // "slot_log_event_read"
QT_MOC_LITERAL(12, 202, 24), // "slot_log_event_empty_arr"
QT_MOC_LITERAL(13, 227, 24), // "slot_stop_read_log_event"
QT_MOC_LITERAL(14, 252, 15), // "slot_disconnect"
QT_MOC_LITERAL(15, 268, 19), // "slot_read_log_event"
QT_MOC_LITERAL(16, 288, 19) // "slot_view_log_event"

    },
    "widget_log_event\0signal_write_data\0\0"
    "signal_bar\0signal_timeout_start\0"
    "signal_timeout_stop\0signal_disable_tab_kn\0"
    "signal_on_pushButton_connect_clicked\0"
    "timeout\0slotRadioToggled\0slotCombo\0"
    "slot_log_event_read\0slot_log_event_empty_arr\0"
    "slot_stop_read_log_event\0slot_disconnect\0"
    "slot_read_log_event\0slot_view_log_event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_log_event[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       3,    1,   92,    2, 0x06 /* Public */,
       4,    1,   95,    2, 0x06 /* Public */,
       5,    0,   98,    2, 0x06 /* Public */,
       6,    2,   99,    2, 0x06 /* Public */,
       7,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  107,    2, 0x08 /* Private */,
       9,    1,  108,    2, 0x08 /* Private */,
      10,    1,  111,    2, 0x08 /* Private */,
      11,    1,  114,    2, 0x0a /* Public */,
      12,    0,  117,    2, 0x0a /* Public */,
      13,    0,  118,    2, 0x0a /* Public */,
      14,    0,  119,    2, 0x0a /* Public */,
      15,    0,  120,    2, 0x0a /* Public */,
      16,    0,  121,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void widget_log_event::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget_log_event *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_write_data((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->signal_bar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signal_timeout_start((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signal_timeout_stop(); break;
        case 4: _t->signal_disable_tab_kn((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->signal_on_pushButton_connect_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->timeout(); break;
        case 7: _t->slotRadioToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->slotCombo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slot_log_event_read((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 10: _t->slot_log_event_empty_arr(); break;
        case 11: _t->slot_stop_read_log_event(); break;
        case 12: _t->slot_disconnect(); break;
        case 13: _t->slot_read_log_event(); break;
        case 14: _t->slot_view_log_event(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (widget_log_event::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log_event::signal_write_data)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (widget_log_event::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log_event::signal_bar)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (widget_log_event::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log_event::signal_timeout_start)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (widget_log_event::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log_event::signal_timeout_stop)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (widget_log_event::*)(bool , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log_event::signal_disable_tab_kn)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (widget_log_event::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_log_event::signal_on_pushButton_connect_clicked)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget_log_event::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_widget_log_event.data,
    qt_meta_data_widget_log_event,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget_log_event::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget_log_event::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget_log_event.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget_log_event::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void widget_log_event::signal_write_data(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void widget_log_event::signal_bar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void widget_log_event::signal_timeout_start(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void widget_log_event::signal_timeout_stop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void widget_log_event::signal_disable_tab_kn(bool _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void widget_log_event::signal_on_pushButton_connect_clicked(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
struct qt_meta_stringdata_TModel_U_t {
    QByteArrayData data[1];
    char stringdata0[9];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TModel_U_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TModel_U_t qt_meta_stringdata_TModel_U = {
    {
QT_MOC_LITERAL(0, 0, 8) // "TModel_U"

    },
    "TModel_U"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TModel_U[] = {

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

void TModel_U::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TModel_U::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_TModel_U.data,
    qt_meta_data_TModel_U,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TModel_U::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TModel_U::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TModel_U.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int TModel_U::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TModel_I_t {
    QByteArrayData data[1];
    char stringdata0[9];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TModel_I_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TModel_I_t qt_meta_stringdata_TModel_I = {
    {
QT_MOC_LITERAL(0, 0, 8) // "TModel_I"

    },
    "TModel_I"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TModel_I[] = {

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

void TModel_I::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TModel_I::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_TModel_I.data,
    qt_meta_data_TModel_I,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TModel_I::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TModel_I::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TModel_I.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int TModel_I::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TModel_rele_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TModel_rele_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TModel_rele_t qt_meta_stringdata_TModel_rele = {
    {
QT_MOC_LITERAL(0, 0, 11) // "TModel_rele"

    },
    "TModel_rele"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TModel_rele[] = {

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

void TModel_rele::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TModel_rele::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_TModel_rele.data,
    qt_meta_data_TModel_rele,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TModel_rele::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TModel_rele::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TModel_rele.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int TModel_rele::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TModel_prog_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TModel_prog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TModel_prog_t qt_meta_stringdata_TModel_prog = {
    {
QT_MOC_LITERAL(0, 0, 11) // "TModel_prog"

    },
    "TModel_prog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TModel_prog[] = {

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

void TModel_prog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TModel_prog::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_TModel_prog.data,
    qt_meta_data_TModel_prog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TModel_prog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TModel_prog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TModel_prog.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int TModel_prog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TModel_ext_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TModel_ext_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TModel_ext_t qt_meta_stringdata_TModel_ext = {
    {
QT_MOC_LITERAL(0, 0, 10) // "TModel_ext"

    },
    "TModel_ext"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TModel_ext[] = {

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

void TModel_ext::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TModel_ext::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_TModel_ext.data,
    qt_meta_data_TModel_ext,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TModel_ext::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TModel_ext::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TModel_ext.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int TModel_ext::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TModel_com_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TModel_com_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TModel_com_t qt_meta_stringdata_TModel_com = {
    {
QT_MOC_LITERAL(0, 0, 10) // "TModel_com"

    },
    "TModel_com"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TModel_com[] = {

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

void TModel_com::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TModel_com::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_TModel_com.data,
    qt_meta_data_TModel_com,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TModel_com::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TModel_com::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TModel_com.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int TModel_com::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TModel_access_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TModel_access_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TModel_access_t qt_meta_stringdata_TModel_access = {
    {
QT_MOC_LITERAL(0, 0, 13) // "TModel_access"

    },
    "TModel_access"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TModel_access[] = {

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

void TModel_access::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TModel_access::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_TModel_access.data,
    qt_meta_data_TModel_access,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TModel_access::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TModel_access::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TModel_access.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int TModel_access::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TModel_diagnos_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TModel_diagnos_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TModel_diagnos_t qt_meta_stringdata_TModel_diagnos = {
    {
QT_MOC_LITERAL(0, 0, 14) // "TModel_diagnos"

    },
    "TModel_diagnos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TModel_diagnos[] = {

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

void TModel_diagnos::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TModel_diagnos::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_TModel_diagnos.data,
    qt_meta_data_TModel_diagnos,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TModel_diagnos::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TModel_diagnos::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TModel_diagnos.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int TModel_diagnos::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TModel_tg_pow_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TModel_tg_pow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TModel_tg_pow_t qt_meta_stringdata_TModel_tg_pow = {
    {
QT_MOC_LITERAL(0, 0, 13) // "TModel_tg_pow"

    },
    "TModel_tg_pow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TModel_tg_pow[] = {

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

void TModel_tg_pow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TModel_tg_pow::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_TModel_tg_pow.data,
    qt_meta_data_TModel_tg_pow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TModel_tg_pow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TModel_tg_pow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TModel_tg_pow.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int TModel_tg_pow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
