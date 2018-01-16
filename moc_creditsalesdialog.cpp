/****************************************************************************
** Meta object code from reading C++ file 'creditsalesdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BuzPOS/creditsalesdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'creditsalesdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CreditSalesDialog_t {
    QByteArrayData data[6];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreditSalesDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreditSalesDialog_t qt_meta_stringdata_CreditSalesDialog = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CreditSalesDialog"
QT_MOC_LITERAL(1, 18, 29), // "on_pushButton_refresh_clicked"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 28), // "on_pushButton_search_clicked"
QT_MOC_LITERAL(4, 78, 35), // "on_lineEdit_customers_returnP..."
QT_MOC_LITERAL(5, 114, 28) // "on_pushButton_filter_clicked"

    },
    "CreditSalesDialog\0on_pushButton_refresh_clicked\0"
    "\0on_pushButton_search_clicked\0"
    "on_lineEdit_customers_returnPressed\0"
    "on_pushButton_filter_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreditSalesDialog[] = {

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
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CreditSalesDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreditSalesDialog *_t = static_cast<CreditSalesDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_refresh_clicked(); break;
        case 1: _t->on_pushButton_search_clicked(); break;
        case 2: _t->on_lineEdit_customers_returnPressed(); break;
        case 3: _t->on_pushButton_filter_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CreditSalesDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CreditSalesDialog.data,
      qt_meta_data_CreditSalesDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreditSalesDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreditSalesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreditSalesDialog.stringdata0))
        return static_cast<void*>(const_cast< CreditSalesDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CreditSalesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
