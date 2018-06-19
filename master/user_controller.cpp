#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QSqlRecord>
#include<QSqlDatabase>
#include<QDateTime>
#include<QDebug>

/*
------------------------登记入住button事件----------------------------------------
#获取 room_id 和 user_id (text)
#若room_id不合法,则弹出消息框:不合法的房间号
#在表room_state中进行查询(room_id是否被使用)
#若该房间已被占用,入住失败,弹出警告对话框:该房间已入住!
#构建元组:
#(room_id,user_id,current_temp=DEFAULT_TEMP,current_wind=0,current_cost=0,check_in_time=CURRENT_TIME)
#将该元组添加到表room_state中
#弹出对话框:登记入住成功!
----------------------------------------------------------------------------------
*/
void MainWindow::on_pbsignin_clicked()
{
    if(ui->leroomid->text().isEmpty() || ui->leuserpwd->text().isEmpty()){
        infoIncompleteError();
        return;
    }
    QString room_id_text = ui->leroomid->text().trimmed();
    QString user_id = ui->leuserpwd->text().trimmed();
    int room_id = room_id_text.toInt();
    if(room_id>0 && room_id<5){
        checkIn(room_id,user_id);
    }else{
        roomIdError();
    }
    refreshLeUser();

}


/*
-------------------------------------退房button事件-----------------------------
#获取room_id 和 user_id
#捕捉当前时间,赋值给变量check_out_time
#读取room_state表,获取current_cost
#弹出对话框显示需要向用户显示的信息
#从room_state中删除该元组
#构建元组 (room_id , check_in_time, check_out_time, user_id, cost)
#将该元组添加到表logfile中
#弹出对话框:退房成功,欢迎下次入住!
--------------------------------------------------------------------------------
*/
void MainWindow::on_pbsignout_clicked()
{
    if(ui->leroomid->text().isEmpty() || ui->leuserpwd->text().isEmpty()){
        infoIncompleteError();
        return;
    }
    QString room_id_text = ui->leroomid->text().trimmed();
    QString user_id = ui->leuserpwd->text().trimmed();
    int room_id = room_id_text.toInt();
    if(room_id>0 && room_id<5){
        checkOut(room_id,user_id);
    }else{
        roomIdError();
    }
    emit tuifang(room_id);
    refreshLeUser();

}

void MainWindow::checkIn(int room_id, QString user_id)
{
    //qDebug()<<room_id<<" "<<user_id;
    QSqlQuery q;
    q.prepare("select * from room_state where room_id=:rid");
    q.bindValue(":rid",room_id);
    q.exec();
    //房间已被占用
    if(q.next()){
        QMessageBox::information(this,tr("Notice"),tr("该房间已被占用!"),QMessageBox::Ok);
        return;
    }else{
        insertTableRoomState(room_id,user_id);
        QMessageBox::information(this,tr("Notice"),tr("登记成功,欢迎入住!"),QMessageBox::Ok);
        return;
    }
}

/*
------------------------------------------退房-----------------------------------------
//提取出q的表项信息,传进insertTableLog
//从数据库中删除该条记录
//弹出对话框:删除成功!
--------------------------------------------------------------------------------------
*/
void MainWindow::checkOut(int room_id, QString user_id)
{
    QSqlQuery q;
    q.prepare("select * from room_state where room_id=:rid and user_id=:uid");
    q.bindValue(":rid",room_id);
    q.bindValue(":uid",user_id);
    q.exec();
    if(q.next()){
        int room_id = q.value(0).toInt();
        QString user_id = q.value(1).toString();
        double current_cost = q.value(4).toDouble();
        QString check_in_time = q.value(5).toString();
        //qDebug()<<room_id<<" "<<user_id<<" "<<check_in_time;
        insertTableLog(room_id, check_in_time,user_id,current_cost);
        deleteTableRoomState(room_id);
        checkOutInfo();
    }else{
        checkOutError();
    }
}

void MainWindow::insertTableRoomState(int room_id,QString user_id)
{
    //获取登记时间
    QDateTime t =QDateTime::currentDateTime();
    QString check_in_time = t.toString("yyyy-MM-dd hh:mm:ss ddd");

    //debug-----------------------------------------------------------------------------------------
    //qDebug()<<t.currentMSecsSinceEpoch();


    QSqlQuery insq;
    //向表room_state插入记录
    insq.prepare("insert into room_state(room_id,user_id,current_temp,current_wind,current_cost,check_in_time,last_open_time,in_connect) values (?,?,?,?,?,?,?,?)");
    insq.bindValue(0,room_id);
    insq.bindValue(1,user_id);
    insq.bindValue(2,-1);
    insq.bindValue(3,-0);
    insq.bindValue(4,0.0);
    insq.bindValue(5,check_in_time);
    insq.bindValue(6,"None");
    insq.bindValue(7,0);
    insq.exec();
}

void MainWindow::insertTableLog(int room_id, QString check_in_time, QString user_id, double cost)
{
    QDateTime t =QDateTime::currentDateTime();
    QString check_out_time = t.toString("yyyy-MM-dd hh:mm:ss ddd");
    QSqlQuery insq;
    insq.prepare("insert into logfile(room_id,check_in_time,check_out_time,user_id,cost) values (?,?,?,?,?)");
    insq.bindValue(0,room_id);
    insq.bindValue(1,check_in_time);
    insq.bindValue(2,check_out_time);
    insq.bindValue(3,user_id);
    insq.bindValue(4,cost);
    insq.exec();
}

void MainWindow::deleteTableRoomState(int room_id)
{
    QSqlQuery q;
    q.prepare("delete from room_state where room_id=:rid");
    q.bindValue(":rid",room_id);
    //q.bindValue(":uid",user_id);
    q.exec();
}

void MainWindow::refreshLeUser()
{
    ui->leroomid->clear();
    ui->leuserpwd->clear();
    ui->leroomid->setFocus();
}


void MainWindow::infoIncompleteError()
{
    QMessageBox::information(this,tr("Notice"),tr("请输入完整信息！"),QMessageBox::Ok);
}

void MainWindow::roomIdError()
{
    QMessageBox::information(this,tr("Notice"),tr("房间号输入不合法!房间号的范围为1-4"),QMessageBox::Ok);
}

void MainWindow::checkOutError()
{
    QMessageBox::information(this,tr("Notice"),tr("用户信息不匹配,请重新检查登记信息!"),QMessageBox::Ok);
}

void MainWindow::checkOutInfo()
{
    QMessageBox::information(this,tr("Notice"),tr("退房成功,欢迎下次入住!"),QMessageBox::Ok);

}


