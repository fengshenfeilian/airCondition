#ifndef LOGIN_H
#define LOGIN_H

#include<QString>
#include<QMessageBox>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDatabase>
#include<QtGui>
#include <QMainWindow>

namespace Ui {  //namespace Ui的声明是为了使ui布局控制和其他的控制代码分离
class login;
}

class login : public QMainWindow //login类继承于QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0); //explicit关键字:显式声明构造函数
    ~login();

private slots:
    void on_pbquit_clicked();
    void on_pblogin_clicked();
    /*
    void mousePressEvent();
    void mouseMoveEvent();
    void mouseReleaseEvent();
    */

private:
    Ui::login *ui;

};

#endif // LOGIN_H
