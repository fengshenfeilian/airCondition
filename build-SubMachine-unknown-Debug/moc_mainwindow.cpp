/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SubMachine/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[27];
    char stringdata0[297];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "askWindSupply"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "setisopen"
QT_MOC_LITERAL(4, 36, 8), // "askLogin"
QT_MOC_LITERAL(5, 45, 9), // "askLogout"
QT_MOC_LITERAL(6, 55, 5), // "state"
QT_MOC_LITERAL(7, 61, 14), // "stopWindSupply"
QT_MOC_LITERAL(8, 76, 10), // "openFailed"
QT_MOC_LITERAL(9, 87, 16), // "onWindSpeedClick"
QT_MOC_LITERAL(10, 104, 11), // "OpenMachine"
QT_MOC_LITERAL(11, 116, 6), // "roomid"
QT_MOC_LITERAL(12, 123, 3), // "obj"
QT_MOC_LITERAL(13, 127, 12), // "CloseMachine"
QT_MOC_LITERAL(14, 140, 11), // "ReceiveWind"
QT_MOC_LITERAL(15, 152, 9), // "SetEnergy"
QT_MOC_LITERAL(16, 162, 8), // "StopWind"
QT_MOC_LITERAL(17, 171, 7), // "toAwait"
QT_MOC_LITERAL(18, 179, 7), // "restart"
QT_MOC_LITERAL(19, 187, 15), // "handleOpenClose"
QT_MOC_LITERAL(20, 203, 18), // "increaseTargetTemp"
QT_MOC_LITERAL(21, 222, 18), // "decreaseTargetTemp"
QT_MOC_LITERAL(22, 241, 8), // "CheckOut"
QT_MOC_LITERAL(23, 250, 7), // "setFreq"
QT_MOC_LITERAL(24, 258, 11), // "regressTemp"
QT_MOC_LITERAL(25, 270, 16), // "changeTargetTemp"
QT_MOC_LITERAL(26, 287, 9) // "judgeTemp"

    },
    "MainWindow\0askWindSupply\0\0setisopen\0"
    "askLogin\0askLogout\0state\0stopWindSupply\0"
    "openFailed\0onWindSpeedClick\0OpenMachine\0"
    "roomid\0obj\0CloseMachine\0ReceiveWind\0"
    "SetEnergy\0StopWind\0toAwait\0restart\0"
    "handleOpenClose\0increaseTargetTemp\0"
    "decreaseTargetTemp\0CheckOut\0setFreq\0"
    "regressTemp\0changeTargetTemp\0judgeTemp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  129,    2, 0x06 /* Public */,
       3,    1,  138,    2, 0x06 /* Public */,
       4,    2,  141,    2, 0x06 /* Public */,
       5,    1,  146,    2, 0x06 /* Public */,
       6,    2,  149,    2, 0x06 /* Public */,
       7,    1,  154,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  157,    2, 0x0a /* Public */,
       9,    0,  158,    2, 0x0a /* Public */,
      10,    2,  159,    2, 0x0a /* Public */,
      13,    0,  164,    2, 0x0a /* Public */,
      14,    1,  165,    2, 0x0a /* Public */,
      15,    1,  168,    2, 0x0a /* Public */,
      16,    1,  171,    2, 0x0a /* Public */,
      17,    0,  174,    2, 0x0a /* Public */,
      18,    0,  175,    2, 0x0a /* Public */,
      19,    0,  176,    2, 0x0a /* Public */,
      20,    0,  177,    2, 0x0a /* Public */,
      21,    0,  178,    2, 0x0a /* Public */,
      22,    0,  179,    2, 0x0a /* Public */,
      23,    1,  180,    2, 0x0a /* Public */,
      24,    0,  183,    2, 0x08 /* Private */,
      25,    0,  184,    2, 0x08 /* Private */,
      26,    0,  185,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QJsonObject,   11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,   12,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->askWindSupply((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->setisopen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->askLogin((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->askLogout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->state((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->stopWindSupply((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->openFailed(); break;
        case 7: _t->onWindSpeedClick(); break;
        case 8: _t->OpenMachine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2]))); break;
        case 9: _t->CloseMachine(); break;
        case 10: _t->ReceiveWind((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 11: _t->SetEnergy((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 12: _t->StopWind((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 13: _t->toAwait(); break;
        case 14: _t->restart(); break;
        case 15: _t->handleOpenClose(); break;
        case 16: _t->increaseTargetTemp(); break;
        case 17: _t->decreaseTargetTemp(); break;
        case 18: _t->CheckOut(); break;
        case 19: _t->setFreq((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->regressTemp(); break;
        case 21: _t->changeTargetTemp(); break;
        case 22: { int _r = _t->judgeTemp();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::askWindSupply)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::setisopen)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::askLogin)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::askLogout)) {
                *result = 3;
            }
        }
        {
            typedef void (MainWindow::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::state)) {
                *result = 4;
            }
        }
        {
            typedef void (MainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopWindSupply)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::askWindSupply(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::setisopen(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::askLogin(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::askLogout(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::state(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::stopWindSupply(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
