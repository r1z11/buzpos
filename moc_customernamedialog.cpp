/****************************************************************************
** Meta object code from reading C++ file 'customernamedialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BuzPOS/customernamedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customernamedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CustomerNameDialog_t {
    QByteArrayData data[7];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomerNameDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomerNameDialog_t qt_meta_stringdata_CustomerNameDialog = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CustomerNameDialog"
QT_MOC_LITERAL(1, 19, 26), // "on_radioButton_old_toggled"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 7), // "checked"
QT_MOC_LITERAL(4, 55, 26), // "on_radioButton_new_toggled"
QT_MOC_LITERAL(5, 82, 28), // "on_pushButton_cancel_clicked"
QT_MOC_LITERAL(6, 111, 24) // "on_pushButton_ok_clicked"

    },
    "CustomerNameDialog\0on_radioButton_old_toggled\0"
    "\0checked\0on_radioButton_new_toggled\0"
    "on_pushButton_cancel_clicked\0"
    "on_pushButton_ok_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomerNameDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    1,   37,    2, 0x08 /* Private */,
       5,    0,   40,    2, 0x08 /* Private */,
       6,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CustomerNameDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CustomerNameDialog *_t = static_cast<CustomerNameDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_radioButton_old_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_radioButton_new_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_cancel_clicked(); break;
        case 3: _t->on_pushButton_ok_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject CustomerNameDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CustomerNameDialog.data,
      qt_meta_data_CustomerNameDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CustomerNameDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomerNameDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CustomerNameDialog.stringdata0))
        return static_cast<void*>(const_cast< CustomerNameDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CustomerNameDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE