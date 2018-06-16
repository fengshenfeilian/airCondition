#ifndef LOGIN_H
#define LOGIN_H

#include<QString>
#include<QMessageBox>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDatabase>
#include<QtGui>
#include <QMainWindow>
#include "netcontroller.h"
#include "constants.h"
namespace Ui {  //namespace Ui的声明是为了使ui布局控制和其他的控制代码分离
class login;
}

class login : public QMainWindow //login类继承于QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0); //explicit关键字:显式声明构造函数
    ~login();
    int roomid;
    QString user_id;
    void failInfo();

public slots:
    void Isopen(QJsonObject);

private slots:
    void on_pbquit_clicked();
    void on_pblogin_clicked();



signals:
    void showMainWindow(int,QJsonObject);

private:
    Ui::login *ui;
    netController nct;
};

#endif // LOGIN_H
