#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QDateTime>

const int DEFAULT_TEMP=25;
/*
登记入住:
#获取 room_id 和 user_id (text)
#在表room_state中进行查询(room_id是否被使用)
#若该房间已被占用,入住失败,弹出警告对话框:该房间已入住!
#构建元组: (room_id,user_id,current_temp=DEFAULT_TEMP,current_wind=0,current_cost=0,check_in_time=CURRENT_TIME)
#将该元祖添加到表room_state中
#弹出对话框:登记入住成功!
*/
void MainWindow::on_pbsignin_clicked()
{
    if(ui->leroomid->text().isEmpty() || ui->leuserpwd->text().isEmpty()){
        QMessageBox::information(this,tr("Notice"),tr("请输入完整信息！"),QMessageBox::Ok);
        return;
    }
    QString room_id = ui->leroomid->text().trimmed();
    QString user_id = ui->leuserpwd->text().trimmed();

    QSqlQuery q;
    q.prepare("select * from room_state where room_id=:rid");
    q.bindValue(":rid",room_id);
    q.exec();
           //房间已被占用
    if(q.next()){
        QMessageBox::information(this,tr("Notice"),tr("该房间已被占用!"),QMessageBox::Ok);
        return;
    }else{
        //获取登记时间
        QDateTime t =QDateTime::currentDateTime();
        QString check_in_time = t.toString("yyyy-MM-dd hh:mm:ss ddd");
        //向表room_state插入记录
        QSqlQuery insq;

    }

}

/*
退房:
#获取room_id 和 user_id
#捕捉当前时间,赋值给变量check_out_time
#读取room_state表,获取current_cost
#弹出对话框显示需要向用户显示的信息
#从room_state中删除该元组
#构建元组 (room_id , check_in_time, check_out_time, user_id, cost)
#将该元组添加到表logfile中
#弹出对话框:退房成功,欢迎下次入住!
*/
void MainWindow::on_pbsignout_clicked()
{

}
