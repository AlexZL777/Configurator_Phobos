/****************************************************************************
** Meta object code from reading C++ file 'widget_update_fw.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DLMS_client_waviot-m1/widget_update_fw.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_update_fw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widget_update_fw_t {
    QByteArrayData data[12];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_update_fw_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_update_fw_t qt_meta_stringdata_widget_update_fw = {
    {
QT_MOC_LITERAL(0, 0, 16), // "widget_update_fw"
QT_MOC_LITERAL(1, 17, 17), // "signal_write_data"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 4), // "data"
QT_MOC_LITERAL(4, 41, 17), // "signal_disconnect"
QT_MOC_LITERAL(5, 59, 36), // "on_pushButton_file_fw_update_..."
QT_MOC_LITERAL(6, 96, 33), // "on_pushButton_auto_update_cli..."
QT_MOC_LITERAL(7, 130, 14), // "slot_read_data"
QT_MOC_LITERAL(8, 145, 15), // "slot_disconnect"
QT_MOC_LITERAL(9, 161, 13), // "slot_start_fw"
QT_MOC_LITERAL(10, 175, 8), // "fileName"
QT_MOC_LITERAL(11, 184, 13) // "slot_timer_fw"

    },
    "widget_update_fw\0signal_write_data\0\0"
    "data\0signal_disconnect\0"
    "on_pushButton_file_fw_update_clicked\0"
    "on_pushButton_auto_update_clicked\0"
    "slot_read_data\0slot_disconnect\0"
    "slot_start_fw\0fileName\0slot_timer_fw"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_update_fw[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   58,    2, 0x08 /* Private */,
       6,    0,   59,    2, 0x08 /* Private */,
       7,    1,   60,    2, 0x0a /* Public */,
       8,    0,   63,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      11,    0,   67,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,

       0        // eod
};

void widget_update_fw::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget_update_fw *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_write_data((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->signal_disconnect(); break;
        case 2: _t->on_pushButton_file_fw_update_clicked(); break;
        case 3: _t->on_pushButton_auto_update_clicked(); break;
        case 4: _t->slot_read_data((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->slot_disconnect(); break;
        case 6: _t->slot_start_fw((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->slot_timer_fw(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (widget_update_fw::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_update_fw::signal_write_data)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (widget_update_fw::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&widget_update_fw::signal_disconnect)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget_update_fw::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_widget_update_fw.data,
    qt_meta_data_widget_update_fw,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget_update_fw::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget_update_fw::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget_update_fw.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget_update_fw::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void widget_update_fw::signal_write_data(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void widget_update_fw::signal_disconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
