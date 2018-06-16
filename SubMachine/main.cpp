#include "mainwindow.h"
#include "netcontroller.h"
#include "constants.h"
#include "login.h"
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QObject>
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    login l;
//    w.show();
    l.show();
    qDebug() << "afsd";
    QObject::connect(&l,SIGNAL(showMainWindow(int,QJsonObject)),&w,SLOT(OpenMachine(int,QJsonObject)));
//    connect(&log,&login::showMainWindow,this,&MainWindow::OpenMachine);
//    QObject::connect(&l,SIGNAL(showMainWindow(int,QString)),&w,SLOT(ShowMainWindow(int,QString)));
//    QObject::connect(&w,SIGNAL(showLogin()),&l,SLOT(ShowLogin()));
    //netController::tsock->connectToHost(IPAddress,PORT);
    return a.exec();
}
