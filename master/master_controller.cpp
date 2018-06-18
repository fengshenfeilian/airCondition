#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datastruct.h"
#include <QDate>


//转入界面:启动控制
void MainWindow::on_pbstart_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//转入界面:模式控制
void MainWindow::on_mode_control_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//转入界面:温度控制
void MainWindow::on_temp_control_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//升高默认温度
void MainWindow::on_temp_plus_clicked()
{

}

//降低默认温度
void MainWindow::on_temp_minus_clicked()
{

}

//转入界面:从机状态显示
/*
扩展功能:
1.按钮事件:删除选中条目
2.按钮事件:修改选中条目
*/
void MainWindow::on_slave_state_clicked()
{
    roomStateModel = new QSqlTableModel(this);
    roomStateModel->setTable("room_state");
    roomStateModel->setHeaderData(roomStateModel->fieldIndex("room_id"),Qt::Horizontal,"房间号");
    roomStateModel->setHeaderData(roomStateModel->fieldIndex("user_id"),Qt::Horizontal,"身份证号");
    roomStateModel->setHeaderData(roomStateModel->fieldIndex("current_temp"),Qt::Horizontal,"当前温度");
    roomStateModel->setHeaderData(roomStateModel->fieldIndex("current_wind"),Qt::Horizontal,"当前风速");
    roomStateModel->setHeaderData(roomStateModel->fieldIndex("current_cost"),Qt::Horizontal,"当前费用");
    roomStateModel->setHeaderData(roomStateModel->fieldIndex("check_in_time"),Qt::Horizontal,"入住时间");
    roomStateModel->select();
    ui->slaveView->setModel(roomStateModel);
    //自适应填充窗口
    ui->slaveView->resizeColumnsToContents();
    ui->slaveView->horizontalHeader();
    for(int i = 0; i < ui->slaveView->horizontalHeader()->count(); i++){
        ui->slaveView->setColumnWidth(i, ui->slaveView->columnWidth(i)+45);
    }
    ui->slaveView->horizontalHeader()->setStretchLastSection(true);
    

    ui->stackedWidget->setCurrentIndex(3);
}


//开机按钮
/*
#设置主机状态 state = open
#只有在state = open的情况下主机的操作才有效
*/
void MainWindow::on_pbopen_clicked()
{
    if(QDate::currentDate().month()>=5||QDate::currentDate().month()<=10){
        workmode=COLDMODE;
    }else{
        workmode=WARMMODE;
    }
    state = OPEN;
}



//关机按钮
void MainWindow::on_pbshutdown_clicked()
{

}

//模式切换按钮
void MainWindow::on_pbmode_clicked()
{

}

/*
//----------------------------------------------------------------------????
#温控信息有关的数据库
*/
void MainWindow::on_pbNetRecord_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


