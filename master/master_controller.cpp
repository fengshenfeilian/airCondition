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

//转入界面:从机状态显示
void MainWindow::on_slave_state_clicked()
{
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
        workmode=COOLMODE;
    }else{
        workmode=HEATMODE;
    }
    state = OPEN;
}

//待机按钮
void MainWindow::on_pbwait_clicked()
{

}

//关机按钮
void MainWindow::on_pbshutdown_clicked()
{

}

void MainWindow::on_pbmode_clicked()
{

}

void MainWindow::on_temp_plus_clicked()
{

}

void MainWindow::on_temp_minus_clicked()
{

}
