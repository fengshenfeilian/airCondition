#include<QString>
#include<QMessageBox>
#include<QtGui>
#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);   //对界面进行初始化
    connect(&nct,&netController::recvOpenAck,this,&login::Isopen);
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
    //从UI获取uid和psd
    roomid=ui->leuid->text().toInt();
    user_id=ui->lepsd->text().trimmed();


    nct.AskLogin(roomid,user_id);


    //管理员登录成功
    /*bool network.verified(uid,psd):
      从控机把用户信息<uid,psd>发给主控进行"用户鉴权"操作;
      true:用户信息与住户信息一致,进入从控机界面
      false: warning......
    */
}

void login::failInfo(){
    QMessageBox::information(this,tr("Warning"),tr("请核对账号密码！"),QMessageBox::Ok);
    ui->leuid->clear();
    ui->lepsd->clear();
    ui->leuid->setFocus();
}

void login::Isopen(QJsonObject obj){
    if(obj.contains("Type")){
            if(obj.take("Reply").toBool() == 1){
                this->failInfo();
            }else{
                this->close();
                emit showMainWindow(roomid,obj);
            }
        }
}
