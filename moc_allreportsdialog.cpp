/****************************************************************************
** Meta object code from reading C++ file 'allreportsdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BuzPOS/allreportsdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'allreportsdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AllReportsDialog_t {
    QByteArrayData data[9];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AllReportsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AllReportsDialog_t qt_meta_stringdata_AllReportsDialog = {
    {
QT_MOC_LITERAL(0, 0, 16), // "AllReportsDialog"
QT_MOC_LITERAL(1, 17, 28), // "on_pushButton_cancel_clicked"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 30), // "on_pushButton_generate_clicked"
QT_MOC_LITERAL(4, 78, 26), // "on_checkBox_single_toggled"
QT_MOC_LITERAL(5, 105, 7), // "checked"
QT_MOC_LITERAL(6, 113, 25), // "on_checkBox_start_toggled"
QT_MOC_LITERAL(7, 139, 23), // "on_checkBox_end_toggled"
QT_MOC_LITERAL(8, 163, 24) // "on_checkBox_cash_clicked"

    },
    "AllReportsDialog\0on_pushButton_cancel_clicked\0"
    "\0on_pushButton_generate_clicked\0"
    "on_checkBox_single_toggled\0checked\0"
    "on_checkBox_start_toggled\0"
    "on_checkBox_end_toggled\0"
    "on_checkBox_cash_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AllReportsDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    1,   46,    2, 0x08 /* Private */,
       6,    1,   49,    2, 0x08 /* Private */,
       7,    1,   52,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,

       0        // eod
};

void AllReportsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AllReportsDialog *_t = static_cast<AllReportsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_cancel_clicked(); break;
        case 1: _t->on_pushButton_generate_clicked(); break;
        case 2: _t->on_checkBox_single_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_checkBox_start_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_checkBox_end_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_checkBox_cash_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject AllReportsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AllReportsDialog.data,
      qt_meta_data_AllReportsDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AllReportsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AllReportsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AllReportsDialog.stringdata0))
        return static_cast<void*>(const_cast< AllReportsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AllReportsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE