/****************************************************************************
** Meta object code from reading C++ file 'localmap.h'
**
** Created: Mon Nov 23 19:05:19 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "localmap.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'localmap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_localMap[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_localMap[] = {
    "localMap\0"
};

const QMetaObject localMap::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_localMap,
      qt_meta_data_localMap, 0 }
};

const QMetaObject *localMap::metaObject() const
{
    return &staticMetaObject;
}

void *localMap::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_localMap))
        return static_cast<void*>(const_cast< localMap*>(this));
    return QWidget::qt_metacast(_clname);
}

int localMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
