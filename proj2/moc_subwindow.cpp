/****************************************************************************
** Meta object code from reading C++ file 'subwindow.h'
**
** Created: Mon Apr 5 22:50:25 2010
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "subwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'subwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_actionMenu[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      24,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_actionMenu[] = {
    "actionMenu\0\0moveOrder()\0attackOrder()\0"
};

const QMetaObject actionMenu::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_actionMenu,
      qt_meta_data_actionMenu, 0 }
};

const QMetaObject *actionMenu::metaObject() const
{
    return &staticMetaObject;
}

void *actionMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_actionMenu))
        return static_cast<void*>(const_cast< actionMenu*>(this));
    return QWidget::qt_metacast(_clname);
}

int actionMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: moveOrder(); break;
        case 1: attackOrder(); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void actionMenu::moveOrder()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void actionMenu::attackOrder()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_mainMenu[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_mainMenu[] = {
    "mainMenu\0\0tutStart()\0"
};

const QMetaObject mainMenu::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_mainMenu,
      qt_meta_data_mainMenu, 0 }
};

const QMetaObject *mainMenu::metaObject() const
{
    return &staticMetaObject;
}

void *mainMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainMenu))
        return static_cast<void*>(const_cast< mainMenu*>(this));
    return QWidget::qt_metacast(_clname);
}

int mainMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tutStart(); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void mainMenu::tutStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
