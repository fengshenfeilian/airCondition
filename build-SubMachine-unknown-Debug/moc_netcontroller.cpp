/****************************************************************************
** Meta object code from reading C++ file 'netcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SubMachine/netcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_netController_t {
    QByteArrayData data[27];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_netController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_netController_t qt_meta_stringdata_netController = {
    {
QT_MOC_LITERAL(0, 0, 13), // "netController"
QT_MOC_LITERAL(1, 14, 11), // "recvOpenAck"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "obj"
QT_MOC_LITERAL(4, 31, 8), // "recvWind"
QT_MOC_LITERAL(5, 40, 13), // "energyAndCost"
QT_MOC_LITERAL(6, 54, 8), // "stopWind"
QT_MOC_LITERAL(7, 63, 2), // "oj"
QT_MOC_LITERAL(8, 66, 8), // "checkOut"
QT_MOC_LITERAL(9, 75, 14), // "centerPowerOff"
QT_MOC_LITERAL(10, 90, 13), // "centerPowerOn"
QT_MOC_LITERAL(11, 104, 4), // "freq"
QT_MOC_LITERAL(12, 109, 8), // "AskLogin"
QT_MOC_LITERAL(13, 118, 6), // "roomid"
QT_MOC_LITERAL(14, 125, 2), // "id"
QT_MOC_LITERAL(15, 128, 13), // "AskWindSupply"
QT_MOC_LITERAL(16, 142, 10), // "targettemp"
QT_MOC_LITERAL(17, 153, 9), // "windspeed"
QT_MOC_LITERAL(18, 163, 4), // "mode"
QT_MOC_LITERAL(19, 168, 9), // "setIsOpen"
QT_MOC_LITERAL(20, 178, 1), // "m"
QT_MOC_LITERAL(21, 180, 9), // "AskLogout"
QT_MOC_LITERAL(22, 190, 5), // "State"
QT_MOC_LITERAL(23, 196, 4), // "temp"
QT_MOC_LITERAL(24, 201, 14), // "StopWindSupply"
QT_MOC_LITERAL(25, 216, 11), // "ReadMessage"
QT_MOC_LITERAL(26, 228, 11) // "lostconnect"

    },
    "netController\0recvOpenAck\0\0obj\0recvWind\0"
    "energyAndCost\0stopWind\0oj\0checkOut\0"
    "centerPowerOff\0centerPowerOn\0freq\0"
    "AskLogin\0roomid\0id\0AskWindSupply\0"
    "targettemp\0windspeed\0mode\0setIsOpen\0"
    "m\0AskLogout\0State\0temp\0StopWindSupply\0"
    "ReadMessage\0lostconnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_netController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       5,    1,  100,    2, 0x06 /* Public */,
       6,    1,  103,    2, 0x06 /* Public */,
       8,    0,  106,    2, 0x06 /* Public */,
       9,    0,  107,    2, 0x06 /* Public */,
      10,    0,  108,    2, 0x06 /* Public */,
      11,    1,  109,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,  112,    2, 0x0a /* Public */,
      15,    4,  117,    2, 0x0a /* Public */,
      19,    1,  126,    2, 0x0a /* Public */,
      21,    1,  129,    2, 0x0a /* Public */,
      22,    2,  132,    2, 0x0a /* Public */,
      24,    1,  137,    2, 0x0a /* Public */,
      25,    0,  140,    2, 0x08 /* Private */,
      26,    0,  141,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonObject,    3,
    QMetaType::Void, QMetaType::QJsonObject,    3,
    QMetaType::Void, QMetaType::QJsonObject,    3,
    QMetaType::Void, QMetaType::QJsonObject,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   13,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   16,   17,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   23,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void netController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        netController *_t = static_cast<netController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->recvOpenAck((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 1: _t->recvWind((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 2: _t->energyAndCost((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 3: _t->stopWind((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 4: _t->checkOut(); break;
        case 5: _t->centerPowerOff(); break;
        case 6: _t->centerPowerOn(); break;
        case 7: _t->freq((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->AskLogin((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->AskWindSupply((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 10: _t->setIsOpen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->AskLogout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->State((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->StopWindSupply((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->ReadMessage(); break;
        case 15: _t->lostconnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (netController::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&netController::recvOpenAck)) {
                *result = 0;
            }
        }
        {
            typedef void (netController::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&netController::recvWind)) {
                *result = 1;
            }
        }
        {
            typedef void (netController::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&netController::energyAndCost)) {
                *result = 2;
            }
        }
        {
            typedef void (netController::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&netController::stopWind)) {
                *result = 3;
            }
        }
        {
            typedef void (netController::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&netController::checkOut)) {
                *result = 4;
            }
        }
        {
            typedef void (netController::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&netController::centerPowerOff)) {
                *result = 5;
            }
        }
        {
            typedef void (netController::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&netController::centerPowerOn)) {
                *result = 6;
            }
        }
        {
            typedef void (netController::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&netController::freq)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject netController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_netController.data,
      qt_meta_data_netController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *netController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *netController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_netController.stringdata0))
        return static_cast<void*>(const_cast< netController*>(this));
    return QObject::qt_metacast(_clname);
}

int netController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void netController::recvOpenAck(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void netController::recvWind(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void netController::energyAndCost(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void netController::stopWind(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void netController::checkOut()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void netController::centerPowerOff()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void netController::centerPowerOn()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void netController::freq(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
