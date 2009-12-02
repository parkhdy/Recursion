/****************************************************************************
** Meta object code from reading C++ file 'worldspace.h'
**
** Created: Tue Dec 1 23:28:21 2009
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
       8,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      20,   11,   11,   11, 0x05,
      71,   64,   32,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     112,   11,   11,   11, 0x0a,
     121,   11,   11,   11, 0x0a,
     132,   11,   11,   11, 0x0a,
     143,   11,   11,   11, 0x0a,
     155,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_worldSpace[] = {
    "worldSpace\0\0moved()\0updateMap()\0"
    "std::vector<std::vector<char> >\0newmap\0"
    "sendMap(std::vector<std::vector<char> >)\0"
    "moveUP()\0moveDOWN()\0moveLEFT()\0"
    "moveRIGHT()\0updateSlice()\0"
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
        case 0: moved(); break;
        case 1: updateMap(); break;
        case 2: { std::vector<std::vector<char> > _r = sendMap((*reinterpret_cast< std::vector<std::vector<char> >(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::vector<std::vector<char> >*>(_a[0]) = _r; }  break;
        case 3: moveUP(); break;
        case 4: moveDOWN(); break;
        case 5: moveLEFT(); break;
        case 6: moveRIGHT(); break;
        case 7: updateSlice(); break;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void worldSpace::moved()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void worldSpace::updateMap()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
std::vector<std::vector<char> > worldSpace::sendMap(std::vector<std::vector<char> > _t1)
{
    std::vector<std::vector<char> > _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
