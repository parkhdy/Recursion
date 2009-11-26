/****************************************************************************
** Meta object code from reading C++ file 'worldspace.h'
**
** Created: Wed Nov 25 19:20:27 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "worldspace.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worldspace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_worldSpace[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      22,   12,   11,   11, 0x05,
      48,   38,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   11,   11,   11, 0x0a,
      73,   11,   11,   11, 0x0a,
      84,   11,   11,   11, 0x0a,
      95,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_worldSpace[] = {
    "worldSpace\0\0dir,nXpos\0movedX(int,int)\0"
    "dir,nYpos\0movedY(int,int)\0moveUP()\0"
    "moveDOWN()\0moveLEFT()\0moveRIGHT()\0"
};

const QMetaObject worldSpace::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_worldSpace,
      qt_meta_data_worldSpace, 0 }
};

const QMetaObject *worldSpace::metaObject() const
{
    return &staticMetaObject;
}

void *worldSpace::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_worldSpace))
        return static_cast<void*>(const_cast< worldSpace*>(this));
    return QWidget::qt_metacast(_clname);
}

int worldSpace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: movedX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: movedY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: moveUP(); break;
        case 3: moveDOWN(); break;
        case 4: moveLEFT(); break;
        case 5: moveRIGHT(); break;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void worldSpace::movedX(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void worldSpace::movedY(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
