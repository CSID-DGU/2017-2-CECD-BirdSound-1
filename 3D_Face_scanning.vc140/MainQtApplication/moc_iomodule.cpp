/****************************************************************************
** Meta object code from reading C++ file 'iomodule.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iomodule.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iomodule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IOModule_t {
    QByteArrayData data[18];
    char stringdata0[300];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IOModule_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IOModule_t qt_meta_stringdata_IOModule = {
    {
QT_MOC_LITERAL(0, 0, 8), // "IOModule"
QT_MOC_LITERAL(1, 9, 14), // "slotTabChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 3), // "idx"
QT_MOC_LITERAL(4, 29, 20), // "slotLoad2dBtnClicked"
QT_MOC_LITERAL(5, 50, 21), // "slotLoadcadBtnClicked"
QT_MOC_LITERAL(6, 72, 20), // "slotSave2dBtnClicked"
QT_MOC_LITERAL(7, 93, 21), // "slotSaveCadBtnClicked"
QT_MOC_LITERAL(8, 115, 23), // "slotCapSave2dBtnClicked"
QT_MOC_LITERAL(9, 139, 24), // "slotCapSaveCadBtnClicked"
QT_MOC_LITERAL(10, 164, 10), // "ViewVertex"
QT_MOC_LITERAL(11, 175, 13), // "ViewWireFrame"
QT_MOC_LITERAL(12, 189, 8), // "ViewFace"
QT_MOC_LITERAL(13, 198, 13), // "ViewEdgedFace"
//QT_MOC_LITERAL(14, 212, 20), // "slotSelectBtnClicked"
QT_MOC_LITERAL(15, 233, 21), // "slotDefaultBtnClicked"
QT_MOC_LITERAL(16, 255, 22), // "slotLandMarkBtnClicked"
QT_MOC_LITERAL(17, 278, 21) // "slotToOrignBtnClicked"

    },
    "IOModule\0slotTabChanged\0\0idx\0"
    "slotLoad2dBtnClicked\0slotLoadcadBtnClicked\0"
    "slotSave2dBtnClicked\0slotSaveCadBtnClicked\0"
    "slotCapSave2dBtnClicked\0"
    "slotCapSaveCadBtnClicked\0ViewVertex\0"
    "ViewWireFrame\0ViewFace\0ViewEdgedFace\0"
   // "slotSelectBtnClicked\0slotDefaultBtnClicked\0"
	"slotDefaultBtnClicked\0"
    "slotLandMarkBtnClicked\0slotToOrignBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IOModule[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x0a /* Public */,
       4,    0,   92,    2, 0x0a /* Public */,
       5,    0,   93,    2, 0x0a /* Public */,
       6,    0,   94,    2, 0x0a /* Public */,
       7,    0,   95,    2, 0x0a /* Public */,
       8,    0,   96,    2, 0x0a /* Public */,
       9,    0,   97,    2, 0x0a /* Public */,
      10,    0,   98,    2, 0x0a /* Public */,
      11,    0,   99,    2, 0x0a /* Public */,
      12,    0,  100,    2, 0x0a /* Public */,
      13,    0,  101,    2, 0x0a /* Public */,
      14,    0,  102,    2, 0x0a /* Public */,
      15,    0,  103,    2, 0x0a /* Public */,
      16,    0,  104,    2, 0x0a /* Public */,
      17,    0,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IOModule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IOModule *_t = static_cast<IOModule *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotTabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slotLoad2dBtnClicked(); break;
        case 2: _t->slotLoadcadBtnClicked(); break;
        case 3: _t->slotSave2dBtnClicked(); break;
        case 4: _t->slotSaveCadBtnClicked(); break;
        case 5: _t->slotCapSave2dBtnClicked(); break;
        case 6: _t->slotCapSaveCadBtnClicked(); break;
        case 7: _t->ViewVertex(); break;
        case 8: _t->ViewWireFrame(); break;
        case 9: _t->ViewFace(); break;
        case 10: _t->ViewEdgedFace(); break;
        case 11: _t->slotSelectBtnClicked(); break;
        case 12: _t->slotDefaultBtnClicked(); break;
        case 13: _t->slotLandMarkBtnClicked(); break;
        case 14: _t->slotToOrignBtnClicked(); break;
        default: ;
        }
    }
}

const QMetaObject IOModule::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_IOModule.data,
      qt_meta_data_IOModule,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *IOModule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IOModule::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IOModule.stringdata0))
        return static_cast<void*>(const_cast< IOModule*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int IOModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
