#include<QString>
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QtGui>
#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    ui->setupUi(this);   //对界面进行初始化
}

login::~login()
{
    delete ui;
}

void login::on_pbquit_clicked()
{
    this->close();
}

void login::on_pblogin_clicked()
{
    //输入信息不完整
    if(ui->leuid->text().isEmpty()||ui->lepsd->text().isEmpty()){
       QMessageBox::information(this,tr("Notice"),tr("请输入完整信息！"),QMessageBox::Ok);
       return;
    }
    QString uid=ui->leuid->text().trimmed();  //从UI获取uid和psd
    QString psd=ui->lepsd->text().trimmed();

    QSqlQuery query;
    query.prepare("select * from superuser where uid=:uid and psd=:psd");
    query.bindValue(":uid",uid);
    query.bindValue(":psd",psd);
    query.exec();
    //管理员登录成功
    if(query.next()){
        MainWindow *w = new MainWindow();
        w->show();
        //w->move ((QApplication::desktop()->width() - w->width())/2,(QApplication::desktop()->height() -w->height())/2);
        this->hide();
    }
    else//管理员登录失败
        {
            QMessageBox::information(this,tr("Warning"),tr("请核对账号密码！"),QMessageBox::Ok);
            ui->leuid->clear();
            ui->lepsd->clear();
            ui->leuid->setFocus();
        }

}

/*

void login::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        {
            m_bPressed = true;
            m_point = event->pos();
        }
}

void login::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}

// 设置鼠标未被按下
void login::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_bPressed = false;
}

*/


