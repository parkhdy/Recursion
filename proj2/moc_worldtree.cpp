/****************************************************************************
** Meta object code from reading C++ file 'worldtree.h'
**
** Created: Mon Apr 19 21:37:31 2010
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "worldtree.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worldtree.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_worldTree[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   11,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_worldTree[] = {
    "worldTree\0\0uni\0updateTree(unit)\0"
};

const QMetaObject worldTree::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_worldTree,
      qt_meta_data_worldTree, 0 }
};

const QMetaObject *worldTree::metaObject() const
{
    return &staticMetaObject;
}

void *worldTree::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_worldTree))
        return static_cast<void*>(const_cast< worldTree*>(this));
    return QWidget::qt_metacast(_clname);
}

int worldTree::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateTree((*reinterpret_cast< unit(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
