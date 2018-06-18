#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datastruct.h"
#include <QDate>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTimer>
#include <QDebug>

/*
-------------------------------------------------------------
模块:界面跳转
-------------------------------------------------------------
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
    showTableNetinfo();
    ui->stackedWidget->setCurrentIndex(4);
}

/* 
---------------------------------------------------------
模块:信号槽事件
---------------------------------------------------------
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
    workmode = COLDMODE;
    DEFAULT_TEMP = 22;
    setLbTemp(22);
    setLbStatusMode();
    setModeInfo();
}

//切换至制热模式
//default 28
void MainWindow::on_pbModeWarm_clicked()
{
    workmode = WARMMODE;
    DEFAULT_TEMP = 28;
    setLbTemp(28);
    setLbStatusMode();
    setModeInfo();
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
------------------------------------------------------------------
模块:功能函数实现
------------------------------------------------------------------
*/

//修改标签<主机开机状态显示>内容
void MainWindow::setLbStatusOn()
{
   if(state == OPEN){
        ui->lbStatusOn->setText(tr("主机状态: 开机"));
    }
    else if(state == SHUTDOWN){
        ui->lbStatusOn->setText(tr("主机状态: 关机"));
    }else{
       ui->lbStatusOn->setText(tr("主机状态: 待机"));
   }
}

//修改标签<主机工作模式显示>内容
void MainWindow::setLbStatusMode()
{
    if(state == OPEN){
        if(workmode == COLDMODE)ui->lbStatusMode->setText(tr("工作模式: 制冷"));
        else ui->lbStatusMode->setText(tr("工作模式: 制热"));
    }else if (state == SHUTDOWN){
        ui->lbStatusMode->setText(tr("工作模式: 无"));
    }
}


/*
---------------------开/关机权限设置-------------------------------------
# 按钮: 关机 | 制冷 | 制热 | 升温 | 降温
# 开机后生效,关机后无效
-------------------------------------------------------------------------
*/
void MainWindow::enableAccess()
{
    ui->pbshutdown->setEnabled(true);
    ui->pbModeCold->setEnabled(true);
    ui->pbModeWarm->setEnabled(true);
    ui->temp_plus->setEnabled(true);
    ui->temp_minus->setEnabled(true);
}

void MainWindow::unableAccess()
{
    ui->pbshutdown->setEnabled(false);
    ui->pbModeCold->setEnabled(false);
    ui->pbModeWarm->setEnabled(false);
    ui->temp_plus->setEnabled(false);
    ui->temp_minus->setEnabled(false);
}

void MainWindow::setDefaultTemp(int temp)
{
    if(temp>35 || temp<18){
        setTempError();
        return;
    }
    if(workmode == COLDMODE){
          if(temp>25){
              setTempError();
              return;
          }
    }else if (workmode == WARMMODE){
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

//刷新操作:
/*
-------------------------更改刷新频率--------------------------------------------
# 功能:
# 改变spinbox的值,获取到一个新的刷新频率(freq=1,1min刷新一次),对累计电费实时刷新
# 计算步骤
---------------------------------------------------------------------------------
*/
void MainWindow::initTableRoomState()
{
    updateTimer = new QTimer(this);
    connect(updateTimer,&QTimer::timeout,this,&MainWindow::updateTableRoomState);
    connect(ui->boxRefreshFreq,SIGNAL(valueChanged(double)),this,SLOT(changeFreq(double)));
    changeFreq(1.0);
    QSqlQuery initq;
    initq.exec("update room_state SET in_connect=0");
}

void MainWindow::changeFreq(double newVal)
{
    updateTimer->stop();
    updateTimer->setInterval(int(newVal*1000));
    updateTimer->start();
}


/*
------------------------刷新room_state表(bug bug bug)---------------------------------------------
# 字段:|房间号|身份证号|当前温度|当前风速|当前费用|入住时间|最近一次开机时间|送风状态|
# 函数流程
# 遍历room_state,依次取出记录,对该记录:
# 取出字段: last_open_time,in_connect, current_cost
# 如果(wind = 0 || !in_connect)则跳过该记录
# 获取当前时间:current_time
# quantum_time = max(current_time-freq,last_open_time)
# current_cost += quantum_time * 1(0.8,1.3) * 电费(5元)
-------------------------------------------------------------------------------------
*/
void MainWindow::updateTableRoomState()
{
    QSqlQuery allq;
    //qDebug()<<"fuck!!!!!";
    allq.prepare("SELECT * FROM room_state");
    allq.exec();
  //  qDebug()<<allq.value(1).toInt();
    while(allq.next()){
    }
}

/*
------------------------显示room_state表---------------------------------------------
# 字段:|房间号|身份证号|当前温度|当前风速|当前费用|入住时间|最近一次开机时间|送风状态|
# 扩展功能:删除一条记录
# 扩展功能:修改一条记录
-------------------------------------------------------------------------------------
*/
void MainWindow::showRoomState()
{
    roomstateModel = new QSqlTableModel(this);
    roomstateModel->setTable("room_state");
    roomstateModel->setHeaderData(roomstateModel->fieldIndex("room_id"),Qt::Horizontal,"房间号");
    roomstateModel->setHeaderData(roomstateModel->fieldIndex("user_id"),Qt::Horizontal,"身份证号");
    roomstateModel->setHeaderData(roomstateModel->fieldIndex("current_temp"),Qt::Horizontal,"当前温度");
    roomstateModel->setHeaderData(roomstateModel->fieldIndex("current_wind"),Qt::Horizontal,"当前风速");
    roomstateModel->setHeaderData(roomstateModel->fieldIndex("current_cost"),Qt::Horizontal,"当前费用");
    roomstateModel->setHeaderData(roomstateModel->fieldIndex("check_in_time"),Qt::Horizontal,"入住时间");
    roomstateModel->setHeaderData(roomstateModel->fieldIndex("last_open_time"),Qt::Horizontal,"最近开机时间");
    roomstateModel->setHeaderData(roomstateModel->fieldIndex("in_connect"),Qt::Horizontal,"连接状态");
    roomstateModel->select();
    ui->slaveView->setModel(roomstateModel);
    //自适应填充窗口
    ui->slaveView->resizeColumnsToContents();
    ui->slaveView->horizontalHeader();
    for(int i = 0; i < ui->slaveView->horizontalHeader()->count(); i++){
        ui->slaveView->setColumnWidth(i, ui->slaveView->columnWidth(i));
    }
    ui->slaveView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::showTableNetinfo()
{
    netinfoModel = new QSqlTableModel(this);
    netinfoModel->setTable("netinfo");
    netinfoModel->setHeaderData(netinfoModel->fieldIndex("room_id"),Qt::Horizontal,"房间号");
    netinfoModel->setHeaderData(netinfoModel->fieldIndex("start_time"),Qt::Horizontal,"请求开始时间");
    netinfoModel->setHeaderData(netinfoModel->fieldIndex("end_time"),Qt::Horizontal,"请求结束时间");
    netinfoModel->setHeaderData(netinfoModel->fieldIndex("user_id"),Qt::Horizontal,"身份证号");
    netinfoModel->setHeaderData(netinfoModel->fieldIndex("is_open"),Qt::Horizontal,"开机请求");
    netinfoModel->setHeaderData(netinfoModel->fieldIndex("current_temp"),Qt::Horizontal,"当前温度");
    netinfoModel->setHeaderData(netinfoModel->fieldIndex("target_temp"),Qt::Horizontal,"目标温度");
    netinfoModel->setHeaderData(netinfoModel->fieldIndex("target_wind"),Qt::Horizontal,"目标风速");
    netinfoModel->setHeaderData(netinfoModel->fieldIndex("cost"),Qt::Horizontal,"费用");
    netinfoModel->select();
    ui->netinfoView->setModel(netinfoModel);
    //自适应填充窗口
    ui->netinfoView->resizeColumnsToContents();
    ui->netinfoView->horizontalHeader();
    for(int i = 0; i < ui->netinfoView->horizontalHeader()->count(); i++){
        ui->netinfoView->setColumnWidth(i, ui->netinfoView->columnWidth(i)+20);
    }
    ui->netinfoView->horizontalHeader()->setStretchLastSection(true);
}

/*
------------------------------------------------------------------
模块:异常信息处理
------------------------------------------------------------------
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

void MainWindow::setModeInfo()
{
    QMessageBox::information(this,tr("Notice"),tr("主机工作模式已变更!"),QMessageBox::Ok);
}
