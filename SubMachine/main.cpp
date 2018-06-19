#include "mainwindow.h"
#include "netcontroller.h"
#include "constants.h"
#include "login.h"
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QObject>
//#pragma execution_character_set("utf-8")

QTcpSocket *sock = new QTcpSocket;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*sock->connectToHost(IP,PORT);
    if(!sock->isOpen())
        qDebug() << "22";*/
     netController n;
    /* QJsonObject swr;
     swr.insert("Type","AskWindSupply");
     swr.insert("Room",1);
    n.send(swr);*/
    MainWindow w;
    login l;
//    w.show();
//    qDebug() << "fff" << endl;
    l.show();
    QObject::connect(&l,SIGNAL(askLogin(int,QString)),&n,SLOT(AskLogin(int,QString)));
    QObject::connect(&n,SIGNAL(recvOpenAck(QJsonObject)),&l,SLOT(Isopen(QJsonObject)));
    QObject::connect(&w,SIGNAL(askWindSupply(int,int,int,int)),&n,SLOT(AskWindSupply(int,int,int,int)));
    QObject::connect(&w,SIGNAL(setisopen(bool)),&n,SLOT(setIsOpen(bool)));
//    QObject::connect(&w,SIGNAL(askLogin(int,QString)),&n,SLOT(AskLogin(int,QString)));
    QObject::connect(&w,SIGNAL(askLogout(int)),&n,SLOT(AskLogout(int)));
    QObject::connect(&w,SIGNAL(state(int,int)),&n,SLOT(State(int,int)));
    QObject::connect(&w,SIGNAL(stopWindSupply(int)),&n,SLOT(StopWindSupply(int)));
    QObject::connect(&n,SIGNAL(centerPowerOff()),&w,SLOT(toAwait()));
    QObject::connect(&n,SIGNAL(checkOut()),&w,SLOT(CheckOut()));
    QObject::connect(&l,SIGNAL(showMainWindow(int,QJsonObject)),&w,SLOT(OpenMachine(int,QJsonObject)));
    QObject::connect(&w,SIGNAL(askLogout(int)),&l,SLOT(backToLogin()));
    QObject::connect(&n,SIGNAL(recvWind(QJsonObject)),&w,SLOT(ReceiveWind(QJsonObject)));
    QObject::connect(&n,SIGNAL(stopWind(QJsonObject)),&w,SLOT(StopWind(QJsonObject)));
    QObject::connect(&n,SIGNAL(centerPowerOn()),&w,SLOT(restart()));
    QObject::connect(&n,SIGNAL(energyAndCost(QJsonObject)),&w,SLOT(SetEnergy(QJsonObject)));
    QObject::connect(&n,SIGNAL(freq(int)),&w,SLOT(setFreq(int)));
    return a.exec();
}
