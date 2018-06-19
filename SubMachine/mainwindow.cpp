#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
//#pragma execution_character_set("utf-8")


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //初始化从控信息
    qsrand(time(NULL));
    ui->setupUi(this);
    for(int i=0;i<4;++i) modeCnt[i] = 0;
    setWindowTitle("空调");
    currentwindspeed=0;
    usedfee=0.0;
    usedenergy=0.0;
    isopen=false;
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏标题栏

    //use button group to make wind speed buttons exclusive
    windSpeedGroup=new QButtonGroup(this);
    windSpeedGroup->addButton(ui->LowWind);
    windSpeedGroup->addButton(ui->MidWind);
    windSpeedGroup->addButton(ui->HighWind);
    connect(ui->LowWind,&QPushButton::clicked,this,&MainWindow::onWindSpeedClick);
    connect(ui->MidWind,&QPushButton::clicked,this,&MainWindow::onWindSpeedClick);
    connect(ui->HighWind,&QPushButton::clicked,this,&MainWindow::onWindSpeedClick);

    connect(ui->OpenClose,&QPushButton::clicked,this,&MainWindow::handleOpenClose);
    connect(ui->IncreaseTemp,&QPushButton::clicked,this,&MainWindow::increaseTargetTemp);
    connect(ui->DecreaseTemp,&QPushButton::clicked,this,&MainWindow::decreaseTargetTemp);

    regresstemptimer=new QTimer(this);
    regresstemptimer->setInterval(2000);//regress temperature per 1 sec
    connect(regresstemptimer,&QTimer::timeout,this,&MainWindow::regressTemp);
/*
    setdelaytimer=new QTimer(this);
    setdelaytimer->setSingleShot(true);
    setdelaytimer->setInterval(1000);//temperature will update until 1 sec with no operation*/
//    connect(setdelaytimer,&QTimer::timeout,this,&MainWindow::changeTargetTemp);

//    judgetimer=new QTimer(this);
//    judgetimer->setInterval(1000);
//    connect(judgetimer,&QTimer::timeout,this,&MainWindow::judgeTemp);

    //connect with net controller

//    connect(&netcon,&netController::recvWind,this,&MainWindow::ReceiveWind);
//  connect(&netcon,&netController::compelCLose,this,&MainWindow::CloseMachine);
//    connect(&netcon,&netController::energyAndCost,this,&MainWindow::SetEnergy);
//    connect(&netcon,&netController::stopWind,this,&MainWindow::StopWind);
//    connect(&netcon,&netController::centerPowerOff,this,&MainWindow::toAwait);
//    connect(&netcon,&netController::centerPowerOn,this,&MainWindow::restart);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRoomID(int newval){
    roomid=newval;
    ui->RoomID->setText(tr("%1").arg(roomid));
}

void MainWindow::openFailed(){
    QMessageBox::warning(this,"开机失败","无法连接中央空调");
}

void MainWindow::onWindSpeedClick(){
    //change wind speed according to current checked button

    if(windSpeedGroup->checkedId()==-2){
        targetWind = 1;
//        changeWindSpeed(1);
    }
    else if(windSpeedGroup->checkedId()==-3){
        targetWind = 2;
//        changeWindSpeed(2);
    }
    else{
        targetWind = 3;
//        changeWindSpeed(3);
    }
//    netcon.AskWindSupply(roomid,targettemp,targetWind,currentmode);
    emit askWindSupply(roomid,targettemp,targetWind,currentmode);
}
//启动从控
void MainWindow::OpenMachine(int roomid,QJsonObject obj){
    this->roomid = roomid;
    currentmode=obj.take("WorkMode").toInt();
    targettemp=temp_targettemp=obj.take("WorkTemperature").toInt();
    roomtemp = 28;
    ui->SetTemp->setText(tr("%1").arg(targettemp));
    if(currentmode==0){
        ui->CurrentMode->setText("制冷");
    }
    else{
        ui->CurrentMode->setText("供暖");
    }

    if(isopen==false){
        isopen=true;
        targetWind = 2;
        currentwindspeed = 0;
        ui->RoomID->setText(tr("%1").arg(roomid));
        ui->OpenClose->setText("关机");
        ui->OpenClose->setEnabled(true);
        //enable all display widget
        ui->IncreaseTemp->setEnabled(true);
        ui->DecreaseTemp->setEnabled(true);

        ui->LowWind->setEnabled(true);
        ui->MidWind->setEnabled(true);
        ui->MidWind->setChecked(true);
        ui->HighWind->setEnabled(true);
        changeWindSpeed(currentwindspeed);//change wind speed to middle

        usedenergy=0;
        ui->UsedEnergy->setText(tr("%1").arg(usedenergy));
        usedfee=0;
        ui->UsedFee->setText(tr("%1").arg(usedfee));

        generateRoomTemp();
        receivecnt=1;
        //judgetimer->start();
        regresstemptimer->start();
    }
    //开机发送送风请求
//    netcon.AskWindSupply(roomid,targettemp,targetWind,currentmode);
//    emit askWindSupply(roomid,targettemp,targetWind,currentmode);
    this->show();
}

void MainWindow::CloseMachine(){
    isopen=false;
//    netcon.setIsOpen(isopen);
    ui->OpenClose->setText("开机");
    //disable all display widget
    ui->IncreaseTemp->setEnabled(false);
    ui->DecreaseTemp->setEnabled(false);
    ui->LowWind->setEnabled(false);
    ui->MidWind->setEnabled(false);
    ui->HighWind->setEnabled(false);
    ui->CurrentMode->setText("-----");
    ui->CurrentTemp->setText("--");
    ui->SetTemp->setText("--");
    ui->UsedEnergy->setText("--");
    ui->UsedFee->setText("--");
    //stop all timer
    //judgetimer->stop();
    regresstemptimer->stop();
    emit setisopen(isopen);
    this->close();
}

void MainWindow::toAwait(){
    isopen=false;
//    netcon.setIsOpen(isopen);
    ui->OpenClose->setText("关机");
//    ui->OpenClose->setEnabled(false);
    //disable all display widget
    ui->IncreaseTemp->setEnabled(false);
    ui->DecreaseTemp->setEnabled(false);
    ui->LowWind->setEnabled(false);
    ui->MidWind->setEnabled(false);
    ui->HighWind->setEnabled(false);
    ui->CurrentMode->setText(tr("%1").arg(currentmode));
    ui->CurrentTemp->setText(tr("%1").arg(roomtemp));
    ui->SetTemp->setText("--");
    ui->UsedEnergy->setText(tr("%1").arg(usedenergy));
    ui->UsedFee->setText(tr("%1").arg(usedfee));
    //stop all timer
   // judgetimer->stop();
    emit setisopen(isopen);
    regresstemptimer->stop();
}

void MainWindow::ReceiveWind(QJsonObject obj){
    if(isopen==false)
        return;
//    QString showstr;
    receivecnt=(receivecnt+1)%15;
    //1 wind packet represent 1 sec wind
    //high speed change temperature per 1sec,mid speed change per 3sec,and low speed change per 5sec
    if(obj.take("Ack").toBool()){
        changeWindSpeed(targetWind);
    }
    /*calculate fee and energy
    if(currentwindspeed==1){
        usedenergy+=0.8/60.0;
        usedfee+=5*0.8/60.0;
    }
    else if(currentwindspeed==2){
        usedenergy+=1.0/60.0;
        usedfee+=5*1.0/60.0;
    }
    else{
        usedenergy+=1.3/60.0;
        usedfee+=5*1.3/60.0;
    }*/

    //ui->UsedEnergy->setText(showstr.setNum(usedenergy,'g',1));
    //ui->UsedFee->setText(showstr.setNum(usedfee,'g',1));
    //report room temp to central aircondition
    //netcon.State(roomid,roomtemp);
}

void MainWindow::handleOpenClose(){
    if(isopen==true){
//        netcon.AskLogout(roomid);
        qDebug() << "shutdown";
        this->close();
        isopen = false;
        emit askLogout(roomid);
//        emit askLogout2();
        /*QTime t;
//        Sleep(1000);
        t.start();
        while(t.elapsed()<1000)
            QCoreApplication::processEvents();*/

//        CloseMachine();
    }
}



void MainWindow::increaseTargetTemp(){
    if(currentmode==0){//cool mode
        if(temp_targettemp<30){
            temp_targettemp++;
            ui->SetTemp->setText(tr("%1").arg(temp_targettemp));
//            setdelaytimer->start();
        }
    }
    else{
        if(temp_targettemp<35){
            temp_targettemp++;
            ui->SetTemp->setText(tr("%1").arg(temp_targettemp));
//            setdelaytimer->start();
        }
    } targettemp = temp_targettemp;
}

void MainWindow::decreaseTargetTemp(){
    if(currentmode==0){//cold mode
        if(temp_targettemp>18){
            temp_targettemp--;
            ui->SetTemp->setText(tr("%1").arg(temp_targettemp));
            //setdelaytimer->start();
        }
    }
    else{
        if(temp_targettemp>25){
            temp_targettemp--;
            ui->SetTemp->setText(tr("%1").arg(temp_targettemp));
            //setdelaytimer->start();
        }
    }
     targettemp = temp_targettemp;
}

void MainWindow::changeWindSpeed(int newspeed){
    for(int i=0;i<4;++i) modeCnt[i] = 0;
    currentwindspeed=newspeed;
//    targettemp = temp_targettemp;
}

//随机生成当前温度
void MainWindow::generateRoomTemp(){
    ui->CurrentTemp->setText(tr("%1").arg(roomtemp));
//    netcon.State(roomid,roomtemp);
    emit state(roomid,roomtemp);
}

void MainWindow::regressTemp(){
    qDebug() << "isopen:" << isopen;
    if(isopen == false) return;
    //regress room temperature based on current work mode
    qDebug() << "judgetemp:" << judgeTemp() << " currentWindspeed:" << currentwindspeed << endl;
    if(judgeTemp() == 0){
        if(currentwindspeed != 0){
//            netcon.StopWindSupply(roomid);
            emit stopWindSupply(roomid);
            return;
        }
    }
    if(judgeTemp() == 1 && currentwindspeed == 0){
//        netcon.AskWindSupply(roomid,targettemp,targetWind,currentmode);
          emit askWindSupply(roomid,targettemp,targetWind,currentmode);
//        return;
    }
    if(currentmode==0){
        ++modeCnt[currentwindspeed];
        switch(currentwindspeed){
        case 0:
            if(modeCnt[currentwindspeed]%15 == 0){
                roomtemp ++;
            }
            break;
        case 1:
            if(modeCnt[currentwindspeed]%15 == 0){
                roomtemp--;
            }
            break;
        case 2:
            if(modeCnt[currentwindspeed]%10 == 0){
                roomtemp--;
            }
            break;
        default:
            if(modeCnt[currentwindspeed]%5 == 0){
                roomtemp--;
            }
            break;
        }

        if(roomtemp>35){
            roomtemp = 35;
        }
        if(roomtemp < 18){
            roomtemp = 18;
        }
    }
    else{
        ++modeCnt[currentwindspeed];
        switch(currentwindspeed){
        case 0:
            if(modeCnt[currentwindspeed]%15 == 0){
                roomtemp --;
            }
            break;
        case 1:
            if(modeCnt[currentwindspeed]%15 == 0){
                roomtemp ++;
            }
            break;
        case 2:
            if(modeCnt[currentwindspeed]%10 == 0){
                roomtemp++;
            }
            break;
        default:
            if(modeCnt[currentwindspeed]%5 == 0){
                roomtemp++;
            }
            break;
        }
        if(roomtemp>35){
            roomtemp = 35;
        }
        if(roomtemp < 18){
            roomtemp = 18;
        }
    }
    qDebug() << "state:" << roomtemp << endl;
    ui->CurrentTemp->setText(tr("%1").arg(roomtemp));
//    netcon.State(roomid,roomtemp);
    emit state(roomid,roomtemp);
}


void MainWindow::changeTargetTemp(){
    targettemp=temp_targettemp;
}

int MainWindow::judgeTemp(){
    //compare current temperature with target temperature w judge the need of wind request
    qDebug() << currentmode << " " << roomtemp << " " <<targettemp << endl;
    if((currentmode==0&&roomtemp>=targettemp+1)||(currentmode==1&&roomtemp<=targettemp-1)){
        return 1;
    }
    return 0;
}

void MainWindow::SetEnergy(QJsonObject obj){
    usedfee = obj.value("Cost").toDouble();
    usedenergy = obj.value("Energy").toDouble();
//    qDebug() << "cost:" << usedfee << " " << usedenergy;
    ui->UsedEnergy->setText(tr("%1").arg(usedenergy));
    ui->UsedFee->setText(tr("%1").arg(usedfee));
}

void MainWindow::StopWind(QJsonObject obj){
    if(obj.take("Ack").toBool()){
        for(int i=0;i<4;++i) modeCnt[i] = 0;
        currentwindspeed = 0;
    }
}


//void MainWindow::ShowMainWindow(int a,QString s) {
//    this->roomid = a;
//    this->user_id = s;
//    this->show();
//}

//void MainWindow::showLogin(){
//    this->hide();
//    this->log.show();
//}

//void MainWindow::on_OpenClose_clicked()
//{
//    showLogin();
//}

void MainWindow::restart(){
    isopen=true;
//    netcon.setIsOpen(isopen);
    ui->OpenClose->setText("关机");
    ui->OpenClose->setEnabled(true);
    //enable all display widget
    ui->IncreaseTemp->setEnabled(true);
    ui->DecreaseTemp->setEnabled(true);
    ui->LowWind->setEnabled(true);
    ui->MidWind->setEnabled(true);
    ui->HighWind->setEnabled(true);
    ui->CurrentMode->setText(tr("%1").arg(currentmode));
    ui->CurrentTemp->setText(tr("%1").arg(roomtemp));
    ui->SetTemp->setText(tr("%1").arg(targettemp));
    ui->UsedEnergy->setText(tr("%1").arg(usedenergy));
    ui->UsedFee->setText(tr("%1").arg(usedfee));
    //start all timer
    //judgetimer->start();
    emit setisopen(isopen);
    regresstemptimer->start();
}

void MainWindow::CheckOut(){
    this->close();
    exit(0);
}


void MainWindow::setFreq(int freq)
{
    this -> regresstemptimer ->stop();
    this->regresstemptimer->setInterval(freq);
    this -> regresstemptimer->start();
}
