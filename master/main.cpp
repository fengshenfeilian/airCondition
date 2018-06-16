#include "mainwindow.h"
#include "login.h"
#include <QApplication>



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

   /* login w;
    w.show();
    */
    MainWindow *w =new MainWindow();
    w->show();

    return a.exec();
}
