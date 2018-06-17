#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datastruct.h"
#include <QDate>
#include<QMessageBox>

/*
 * -------------------------------------------------------------
 *模块:主机控制台的界面跳转
 * -------------------------------------------------------------
*/
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
    showRoomState();
    ui->stackedWidget->setCurrentIndex(3);
}

//转入界面:温控请求信息显示
void MainWindow::on_pbNetRecord_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

/* 
 *---------------------------------------------------------
 *模块:主机控制台内的信号槽实现
 *---------------------------------------------------------
*/

//开机按钮
void MainWindow::on_pbopen_clicked()
{
    if(state == OPEN){
        hasOpenError();
        return;
    }else{
        if(QDate::currentDate().month()>=5||QDate::currentDate().month()<=10){
            workmode=COLDMODE;
        }else{
            workmode=WARMMODE;
        }
        state = OPEN;
        setLbStatusOn();
        setLbStatusMode();
        enableAccess();
        openSuccessInfo();
    }
}

//关机按钮
void MainWindow::on_pbshutdown_clicked()
{
    if(state == SHUTDOWN){
        hasCloseError();
        return;
    }else{
        state = SHUTDOWN;
        setLbStatusOn();
        setLbStatusMode();
        unableAccess();
        closeSuccessInfo();
    }
}

//切换至制冷模式
//default = 22
void MainWindow::on_pbModeCold_clicked()
{
    DEFAULT_TEMP = 22;
}

//切换至制热模式
//default 28
void MainWindow::on_pbModeWarm_clicked()
{
    DEFAULT_TEMP = 28;
}

//升高默认温度
void MainWindow::on_temp_plus_clicked()
{
    setDefaultTemp(DEFAULT_TEMP+1);
}

//降低默认温度
void MainWindow::on_temp_minus_clicked()
{
    setDefaultTemp(DEFAULT_TEMP-1);
}


/*
 *------------------------------------------------------------------
 *模块:功能函数实现
 *------------------------------------------------------------------
*/

//修改标签<主机开机状态显示>内容
void MainWindow::setLbStatusOn()
{
   if(state == OPEN){
        ui->lbStatusOn->setText(tr("主机状态:开机"));
    }
    else if(state == SHUTDOWN){
        ui->lbStatusOn->setText(tr("主机状态:关机"));
    }else{
       ui->lbStatusOn->setText(tr("主机状态:待机"));
   }
}

//修改标签<主机工作模式显示>内容
void MainWindow::setLbStatusMode()
{
    if(state == OPEN){
        if(workmode == COLDMODE)ui->lbStatusMode->setText(tr("工作模式:制冷"));
        else ui->lbStatusMode->setText(tr("工作模式:制热"));
    }else if (state == SHUTDOWN){
        ui->lbStatusMode->setText(tr("工作模式:无"));
    }
}

//开机之后赋予MainWindow权限:
/*
#允许进行的按钮操作:
*/
void MainWindow::enableAccess()
{
    ui->pbshutdown->setEnabled(true);
    ui->pbModeCold->setEnabled(true);
    ui->pbModeCold->setEnabled(true);
    ui->temp_plus->setEnabled(true);
    ui->temp_minus->setEnabled(true);
}

void MainWindow::unableAccess()
{
    ui->pbshutdown->setEnabled(false);
    ui->pbModeCold->setEnabled(false);
    ui->pbModeCold->setEnabled(false);
    ui->temp_plus->setEnabled(false);
    ui->temp_minus->setEnabled(false);
}

void MainWindow::setDefaultTemp(int temp)
{
    if(temp>35 || temp<18){
        setTempError();
        return;
    }
    if(state == COLDMODE){
          if(temp>25){
              setTempError();
              return;
          }
    }else if (state == WARMMODE){
        if(temp<25){
            setTempError();
            return;
        }
    }
    DEFAULT_TEMP = temp;
    setLbTemp(temp);
}

void MainWindow::setLbTemp(int temp)
{
    ui->lbDefaultTemp->setText(tr("%1").arg(temp));
}

/*
扩展功能:-----------------------------------------------------------------
1.按钮事件:删除选中条目
2.按钮事件:修改选中条目
*/
void MainWindow::showRoomState()
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
}


/*
 *------------------------------------------------------------------
 *模块:异常处理
 *------------------------------------------------------------------
*/
void MainWindow::hasOpenError()
{
    QMessageBox::information(this,tr("Notice"),tr("中央空调正在运行,无法重复开启!"),QMessageBox::Ok);
}

void MainWindow::hasCloseError()
{
    QMessageBox::information(this,tr("Notice"),tr("中央空调已关闭,无法重复关闭!"),QMessageBox::Ok);
}


void MainWindow::openSuccessInfo()
{
    QMessageBox::information(this,tr("Notice"),tr("中央空调已成功开启!"),QMessageBox::Ok);
}

void MainWindow::closeSuccessInfo()
{
    QMessageBox::information(this,tr("Notice"),tr("中央空调已成功关闭!"),QMessageBox::Ok);
}

void MainWindow::setTempError()
{
    QMessageBox::information(this,tr("Notice"),tr("温度设置失败!"),QMessageBox::Ok);
}

