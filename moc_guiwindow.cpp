/****************************************************************************
** Meta object code from reading C++ file 'guiwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "guiwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guiwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GuiWindow_t {
    QByteArrayData data[9];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GuiWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GuiWindow_t qt_meta_stringdata_GuiWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "GuiWindow"
QT_MOC_LITERAL(1, 10, 11), // "dirSelector"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "checked"
QT_MOC_LITERAL(4, 31, 12), // "fileSelector"
QT_MOC_LITERAL(5, 44, 15), // "segmentSelector"
QT_MOC_LITERAL(6, 60, 13), // "organsizeFile"
QT_MOC_LITERAL(7, 74, 15), // "reconstructFile"
QT_MOC_LITERAL(8, 90, 13) // "comboBoxValue"

    },
    "GuiWindow\0dirSelector\0\0checked\0"
    "fileSelector\0segmentSelector\0organsizeFile\0"
    "reconstructFile\0comboBoxValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GuiWindow[] = {

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
       1,    1,   44,    2, 0x08 /* Private */,
       4,    1,   47,    2, 0x08 /* Private */,
       5,    1,   50,    2, 0x08 /* Private */,
       6,    1,   53,    2, 0x08 /* Private */,
       7,    1,   56,    2, 0x08 /* Private */,
       8,    1,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void GuiWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GuiWindow *_t = static_cast<GuiWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dirSelector((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->fileSelector((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->segmentSelector((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->organsizeFile((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->reconstructFile((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->comboBoxValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject GuiWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GuiWindow.data,
      qt_meta_data_GuiWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GuiWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GuiWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GuiWindow.stringdata0))
        return static_cast<void*>(const_cast< GuiWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GuiWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
