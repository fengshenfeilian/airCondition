#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSqlQuery>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //connect to database : master
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/marco/master");
    if(!db.open()){
        qDebug()<<"database open failed";
    }else{
        qDebug()<<"database open success";
    }
    //login w;
    //w.show();

    MainWindow *w =new MainWindow();
    w->show();
    w->move ((QApplication::desktop()->width() - w->width())/2,(QApplication::desktop()->height() -w->height())/2);
    //-------added by zwj--------------------------
    NetController n;
    QObject::connect(w,SIGNAL(sendStateToMainWindow(int)),&n,SLOT(recvStateFromMainWindow(int)));
    QObject::connect(&n,SIGNAL(toMainWindow()),w,SLOT(stateActToMasterState()));
    QObject::connect(w,SIGNAL(sendTempToMainWindow(int)),&n,SLOT(recvTempFromMainWindow(int)));
    QObject::connect(&n,SIGNAL(toMainWindow2()),w,SLOT(tempActToMasterState()));
    QObject::connect(w,SIGNAL(sendWorkmodeToMainWindow(int)),&n,SLOT(recvWorkmodeFromMainWindow(int)));
    QObject::connect(&n,SIGNAL(toMainWindow3()),w,SLOT(workmodeActTo()));

    QObject::connect(w,SIGNAL(closeConnection()),&n,SLOT(sendPowerOffToSlave()));
    QObject::connect(w,SIGNAL(tuifang(int)),&n,SLOT(removeSlaveInfo(int)));
    QObject::connect(w,SIGNAL(sendon()),&n,SLOT(sendPowerOnToSlave()));

    //----------------------------------------

    return a.exec();
}
