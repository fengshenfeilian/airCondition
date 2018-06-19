#include "NetController.h"
#include "constant.h"
#include "datastruct.h"
#include "tcpclientsocket.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QString>

/*
#如何更新end_time?
#当下一个同房间的请求发来的时候,更新当前请求的end_time
*/

/*
当日报表:
房间号 | 开机次数 | 当日费用 | 
#如果当前时间是00:00,新建一条记录: daily_report
#
#t.currentMSecsSinceEpoch(): (current_time - Eopch_time)

*/

/*
#开机次数计算 : 收到每一次开机请求后,开机次数+1
#当日费用怎么算?
#daily_cost += sum( netInfo.cost )
#daily_cost += 昨日正在进行的送风和持续到明天的送风
*/



NetController::NetController(QObject *parent) :
    QTcpServer(parent)
{
    this->port = 6666;
    this->startListening();
    qDebug() << "start\n";
}
/*
void Server::checkAdminInfo(QString id, QString password)
{
    //管理员登陆成功
    emit sendAdminInfoToUi(isCorrect);
    if(isCorrect)
        this->startListening();
}
*/

//发送登陆请求回复
void NetController::sendReply(QTcpSocket* tsock,int reply,int workmode,int worktemp){
    QJsonObject rfl;
    rfl.insert("Type","ReplyForLogin");
    rfl.insert("Reply",reply);
    rfl.insert("WorkMode",workmode);
    rfl.insert("WorkTemperature",worktemp);
    qDebug()<<rfl<<endl;//------------------------------------------------------------------------debug
    send(tsock,rfl);
}
//发送能耗和费用信息
void NetController::sendEnergyAndCost(QTcpSocket* tsock,double energy,double cost)
{
    QJsonObject eac;
    eac.insert("Type","EnergyAndCost");
    eac.insert("Energy",energy);
    eac.insert("Cost",cost);
    send(tsock,eac);
}
//发送接收状态信息回复
void NetController::sendReplyForState(QTcpSocket* tsock,bool ack){
    QJsonObject rfs;
    rfs.insert("Type","ReplyForState");
    rfs.insert("Ack",ack);
    send(tsock,rfs);
}
//发送请求送风回复
void NetController::sendReplyForWindSupply(QTcpSocket* tsock,bool ack){
    QJsonObject rfws;
    rfws.insert("Type","ReplyForWindSupply");
    rfws.insert("Ack",ack);
    send(tsock,rfws);
}
//发送停止送风回复
void NetController::sendReplyForStopWindSupply(QTcpSocket* tsock,bool ack){
    QJsonObject rfs;
    rfs.insert("Type","ReplyForStopWindSupply");
    rfs.insert("Ack",ack);
    send(tsock,rfs);
}
//发送开机信号
void NetController::sendPowerOn(QTcpSocket* tsock)
{
    QJsonObject po;
    po.insert("Type","PowerOn");
    send(tsock,po);
}
//发送关机信号
void NetController::sendPowerOff(QTcpSocket* tsock){
    QJsonObject pof;
    pof.insert("Type","PowerOff");
    send(tsock,pof);
}

//服务器监视socket
void NetController::ReadMessage(int no,QJsonObject obj)
{
   emit toMainWindow();
   int state = this->MasterState;
   qDebug() << "readmessage:" << endl;
   qDebug() << obj <<endl;
   if(state == OPEN || state == WAIT){
       state = OPEN;
       processMessage(no,obj);
   }
}

/*
----------------------------------------数据包处理模块------------------------------
#共收到五种包:
# 从机请求登录 | 从机请求注销 | 从机送风请求 | 从机停风请求 | 从机当前温度
#不同包需要处理的不同字段:
#从机请求登录: 更新<is_connect>信息
#从机请求注销: 更新<is_connect>信息；更新<current_wind>信息；更新<current_temp>信息
#维护数据表netinfoTable

#需要发送的包:
# 当前累计费用
------------------------------------------------------------------------------------
*/
void NetController::processMessage(int no, QJsonObject obj)
{
    QString type = obj.value("Type").toString();
    //从机请求登录
    if(type == "AskLogin"){
        judgeLogin(no,obj);//-------------------------------------------------ok
        insertTableNetinfo(obj,ASKLOGIN);
    }
    //收到送风请求
    else if(type == "AskWindSupply"){
        updateTableRoomStateTup(obj,SENDWIND);
        judgeWindSupply(no,obj);
        insertTableNetinfo(obj,SENDWIND);
         //sendReplyForWindSupply(true);
    }
    //收到停止送风请求
    else if(type == "StopWindSupply"){
        //handleStop();
        stopSlaveWind(no,obj);
        updateTableRoomStateTup(obj,STOPWIND);
        //sendReplyForStopWindSupply(true);
    }
    //维护从控表->当前温度信息
    else if(type == "State"){
        updateTableRoomStateTup(obj,UPDATETEMP);
        modifySlaveTemp(no,obj);
        insertTableNetinfo(obj,UPDATETEMP);
        //sendReplyForState(no,true);
    }
    //删除roomid_close的信息表
    else if(type == "AskLogout"){   //------------------------------------------ok
        int id = obj.value("Room").toInt();
//        removeSlaveInfo(id);
        logoutSuccess(obj);
        insertTableNetinfo(obj,ASKLOGOUT);
    }
    else if(type == "ReplyForEnergyAndCost" || type == "ReplyForPowerOn" || type == "ReplyForPoserOff"){
        return;
    }

}

//子模块：发送JSON
void NetController::send(QTcpSocket* tsock,QJsonObject json)
{
        QJsonDocument doc;
        doc.setObject(json);
        QByteArray byte = doc.toJson(QJsonDocument::Compact);
        QString str(byte);
        QByteArray blocks;
        QDataStream out(&blocks,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_5);
        out << (quint16)0;
        out << str;
        out.device()->seek(0);
        out << (quint16)(blocks.size() - sizeof(quint16));
        tsock->write(blocks);
        //tcpList.removeFirst();
        qDebug() << json.value("Type") << endl;
}

void NetController::judgeWindSupply(int no,QJsonObject obj){
    int roomid = obj.value("Room").toInt();
    int askTemp = obj.value("Temperature").toInt();
    int askWindSpeed = obj.value("WindSpeed").toInt();
    int windType = obj.value("WindType").toInt();
    //送风请求后续操作
    TcpClientSocket* tcpClientSocket;
    int index;
    for(int i = 0; i < tcpClientSocketList.count(); i++){
        tcpClientSocket = tcpClientSocketList.at(i);
        if(tcpClientSocket->no == no){
            index = i;
            break;
        }
    }
    sendReplyForWindSupply(tcpClientSocket,true);
}

void NetController::removeSlaveInfo(int room_id){
    if(room_list.contains(room_id))
    {
        room_list[room_id]->close();
        room_list.remove(room_id);
    }
    //从机关机
}

void NetController::stopSlaveWind(int no,QJsonObject obj){
    int roomid = obj.value("Room").toInt();
    TcpClientSocket* tcpClientSocket;
    int index;
    for(int i = 0; i < tcpClientSocketList.count(); i++){
        tcpClientSocket = tcpClientSocketList.at(i);
        if(tcpClientSocket->no == no){
            index = i;
            break;
        }
    }
    //从机停风
    sendReplyForStopWindSupply(tcpClientSocket,true);
}

void NetController::modifySlaveTemp(int no,QJsonObject obj){
    int roomid = obj.value("Room").toInt();
    int current_temp = obj.value("Temperature").toInt();
    //从机的当前温度
    TcpClientSocket* tcpClientSocket;
    int index;
    for(int i = 0; i < tcpClientSocketList.count(); i++){
        tcpClientSocket = tcpClientSocketList.at(i);
        if(tcpClientSocket->no == no){
            index = i;
            break;
        }
    }
    sendReplyForState(tcpClientSocket,true);
}

void NetController::incomingConnection(qintptr socketDescriptor){
    TcpClientSocket *tcpClientSocket = new TcpClientSocket(this);
    tcpClientSocket->no = this->no;
    no++;
    connect(tcpClientSocket,SIGNAL(sendToServer(int,QJsonObject)),
            this,SLOT(ReadMessage(int,QJsonObject)));
    connect(tcpClientSocket,SIGNAL(disconnected(int)),
            this,SLOT(slotDisconnected(int)));
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    tcpClientSocket->setSocketOption(QAbstractSocket::LowDelayOption,1);
    tcpClientSocketList.append(tcpClientSocket);
    qDebug() << "222\n";
}

void NetController::slotDisconnected(int descriptor){
    for(int i=0;i<tcpClientSocketList.count();i++){
        TcpClientSocket *item = tcpClientSocketList.at(i);
        if(item->socketDescriptor() == descriptor){
//            int no = item->no;
            tcpClientSocketList.removeAt(i);
            return;
        }
    }
    return;
}

//监听
void NetController::startListening()
{
    no = 0;
    this->listen(QHostAddress::Any, port);
    this->billTimer = new QTimer();
    connect(billTimer, SIGNAL(timeout()), this, SLOT(sendBillToSlave()));

    this->billTimer->start(5000); //默认五秒发送一次账单信息
    /*
    this->refreshTimer = new QTimer();
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(sendStateQueryPackageToSlave()));
    this->refreshTimer->start((int)(refreshRate * 1000));
    emit sendUpdateInfoToUi(refreshRate, workMode, status);*/
}

void NetController::closeServer()
{
    billTimer->stop();
    delete billTimer;
    /*
    refreshTimer->stop();
    delete refreshTimer;
*/
    this->tcpClientSocketList.clear();
    this->close();
}


/*
-------------------------从机登录校验模块-----------------------------------------
#在room_state中查找由<room_id,user_id>唯一标识的tuple
#如果成功找到,则判断从机是否已建立连接(in_connect)
#与从机建立连接(in_connect=1)
#更新数据表room_state last_open_time=now
----------------------------------------------------------------------------------
*/
void NetController::judgeLogin(int no,QJsonObject obj)
{
    emit toMainWindow2();
    emit toMainWindow3();
   // qDebug() << this->MasterState << "************************************";
    int id = obj.value("Room").toInt();
    QString user_id = obj.value("ID").toString();
    TcpClientSocket* tcpClientSocket;
    int index;
    for(int i = 0; i < tcpClientSocketList.count(); i++){
        tcpClientSocket = tcpClientSocketList.at(i);
        if(tcpClientSocket->no == no){
            index = i;
            break;
        }
     }
    //if(房间号与身份证号匹配,且 !in_connect )登录成功
    int logAck;
    if(loginSuccess(obj)){
        TcpClientSocket* broad_tcp = tcpClientSocket;//--------------------------new
        room_list.insert(id,broad_tcp);
        logAck = 0;
    }else{
        logAck = 1;
    }
    sendReply(tcpClientSocket,logAck,this->workmode,this->DEFAULT_TEMP);
}

bool NetController::loginSuccess(QJsonObject obj)
{
    int room_id = obj.value("Room").toInt();
    QString user_id = obj.value("ID").toString();
    QSqlQuery q;
    q.prepare("SELECT * FROM room_state WHERE room_id=:rid AND user_id=:uid");
    q.bindValue(":rid",room_id);
    q.bindValue(":uid",user_id);
    q.exec();
    if(q.next()){
        int in_connect = q.value(7).toInt();
        if(in_connect){
            return 0;
        }else{
            updateTableRoomStateTup(obj,ASKLOGIN);
            return 1;
        }
    }else{
        return 0;
    }
}


/*
-------------------------从机注销校验模块-----------------------------------------
#在room_state中查找由<room_id,user_id>唯一标识的tuple
#如果成功找到,则判断从机是否已建立连接(in_connect)
#与从机断开连接(in_connect=0)
#更新数据表room_state: is_connect=0, current_wind=0, current_temp = -1;
----------------------------------------------------------------------------------
*/

void NetController::logoutSuccess(QJsonObject obj)
{
    int room_id = obj.value("Room").toInt();
    QSqlQuery q;
    q.prepare("SELECT * FROM room_state WHERE room_id=:rid");
    q.bindValue(":rid",room_id);
    q.exec();
    if(q.next()){
        updateTableRoomStateTup(obj,ASKLOGOUT);
        q.exec();
        return;
    }
    return;
}

/*
--------------------------room_state更新模块--------------------------------------
SENDWIND: current_wind
STOPWIND: current_wind = 0,
UPDATETEMP: current_tep
ASKLOGIN:   last_open_time=current time, in_connect=1
ASKLOGOUT:  current_wind=0, current_temp=-1 in_connect=0;
----------------------------------------------------------------------------------
*/
/*
-----------------------------------roomstate表字段----------------------------------------------------------
room_id | user_id  | current_temp  | current_wind  | current_cost  | check_in_time | last_open_time | in_connect
----------------------------------------------------------------------------------------------------------
*/
void NetController::updateTableRoomStateTup(QJsonObject obj, int objType)
{
    int room_id = obj.value("Room").toInt();
    QString user_id;
    int current_temp,current_wind,in_connect;

    QSqlQuery q;
    QDateTime t_text =QDateTime::currentDateTime();
    QString t = t_text.toString("yyyy-MM-dd hh:mm:ss ddd");

    switch(objType){
    case SENDWIND:
        //current_temp =obj.value("Temperature").toInt();
        current_wind = obj.value("WindSpeed").toInt();
        q.prepare("UPDATE room_state SET current_wind=:cwind WHERE room_id=:rid");
        q.bindValue(":cwind",current_wind);
        q.bindValue(":rid",room_id);
        q.exec();
        break;
    case STOPWIND:
        q.prepare("UPDATE room_state SET current_wind=0 WHERE room_id=:rid");
        q.bindValue(":rid",user_id);
        q.exec();
        break;
    case UPDATETEMP:
        current_temp = obj.value("Temperature").toInt();
        q.prepare("UPDATE room_state SET current_temp=:ctemp WHERE room_id=:rid");
        q.bindValue(":ctemp",current_temp); //更新当前温度
        q.bindValue(":rid",room_id);
        q.exec();
        break;
    case ASKLOGIN:
        q.prepare("UPDATE room_state SET in_connect=:connect_info,last_open_time=:time WHERE room_id=:rid");
        q.bindValue(":connect_info",1); //建立连接
        q.bindValue(":time",t); //更新登录时间
        q.bindValue(":rid",room_id);
        q.exec();

        break;
    case ASKLOGOUT:
        q.prepare("UPDATE room_state SET in_connect=:connect_info,current_wind=:cwind,current_temp=:ctemp WHERE room_id=:rid");
        q.bindValue(":connect_info",0);  //断开连接
        q.bindValue(":rid",room_id);
        q.bindValue(":cwind",0);    //风速为0
        q.bindValue(":ctemp",-1); //从控机温度未知
        q.exec();
        break;
    }
}



/*
----------------------------------netinfo插入模块-------------------------------------
*/
/*
-----------------------------------netinfo表字段----------------------------------------------------------
room_id | start_time  | end_time  | user_id  | is_open  | current_temp | target_temp | target_wind  | cost | run
----------------------------------------------------------------------------------------------------------
*/
void NetController::insertTableNetinfo(QJsonObject obj,int objType)
{
    int room_id = obj.value("Room").toInt();
    int target_temp;
    int target_wind;
    int current_wind;
    int current_temp;
    int run;
    int m_time;
    double current_cost;
    QString user_id,start_time,end_time;
    QDateTime time1,time2;

    time1 = QDateTime::currentDateTime(); //start_time
    start_time = time1.toString("yyyy-MM-dd hh:mm:ss ddd");

    QSqlQuery q;
    // user_id | current_temp
    q.prepare("SELECT * FROM room_state WHERE room_id=:rid");
    q.bindValue(":rid",room_id);
    q.exec();
    if (q.next()){
        user_id = q.value(3).toString();
        current_temp = q.value(5).toInt();
    }

    switch(objType){
    //送风请求
    case  SENDWIND:
        killAsk(room_id);
        target_temp = obj.value("Temperature").toInt();
        target_wind = obj.value("WindSpeed").toInt();
        run = 1;
        end_time = "--";
        q.prepare("INSERT INTO netinfo (room_id,start_time,end_time,user_id,is_open,current_temp,target_temp,target_wind,cost,run) values (?,?,?,?,?,?,?,?,?,?)");
        q.bindValue(0,room_id);
        q.bindValue(1,start_time);
        q.bindValue(2,end_time);
        q.bindValue(3,user_id);
        q.bindValue(4,0);
        q.bindValue(5,current_temp);
        q.bindValue(6,target_temp);
        q.bindValue(7,target_wind);
        q.bindValue(8,0.0);
        q.bindValue(9,run);
        q.exec();
       // qDebug()<<start_time<<" "<<end_time<<" "<<user_id<<" "<<current_temp<<" "<<target_temp<<" "<<target_wind<<endl;
     //   qDebug()<<objType<< "fuck!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<room_id<<endl;
        break;
    //停风请求
    case  STOPWIND:
        killAsk(room_id);
        break;
    case  UPDATETEMP:  //定时显示温度,这个信息不需要保存
        //current_temp = obj.value("Temprature").toInt();
        break;
    case  ASKLOGIN: //登录信息,需要保存
        break;
    case  ASKLOGOUT:   //注销信息,不需要保存
        killAsk(room_id);
        break;
    }

}


//------------------------------结束当前正在响应的请求-----------------------
//一个房间(room_id)只能同时响应一个请求
void NetController::killAsk(int room_id)
{
    //找到房间号为room_id,并且正在运行的请求
    QSqlQuery q;
    q.prepare("SELECT * FROM netinfo WHERE room_id=:rid AND run=1");
    q.bindValue(":rid",room_id);
    q.exec();
    if(q.next()){
        QString start_time = q.value(1).toString();
        int current_wind = q.value(7).toInt();

        QString end_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");

        QDateTime time1 = QDateTime::fromString(start_time,"yyyy-MM-dd hh:mm:ss ddd");
        QDateTime time2 = QDateTime::fromString(end_time,"yyyy-MM-dd hh:mm:ss ddd");
        //计算两个时间的时间差
        int m_time = getMinuteTo(time1,time2);

        qDebug()<<"fuck!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qDebug()<<m_time<<endl;

        double current_cost = WindRate[current_wind] * m_time * PowerRate;
        q.prepare("UPDATE netinfo SET end_time=:etime,cost=:cost,run=:run WHERE room_id=:rid AND run=1");
        q.bindValue(":etime",end_time);
        q.bindValue(":cost",current_cost);
        q.bindValue(":rid",room_id);
        q.bindValue(":run",0);
        q.exec();
    }
}

//--------------------------------向从控机发送当前累计费用信息------------------------
void NetController::sendBillToSlave()
{
    for (QMap<int,TcpClientSocket*>::iterator it = room_list.begin();it != room_list.end();it++)
    {
        int room_id = it.key();
        //查找到roomid对应的energy和cost
        double energy = getEnergyFromTableRoomState(room_id);
        double cost = energy * PowerRate;
        sendEnergyAndCost(it.value(),energy,cost);
    }
}

double NetController::getEnergyFromTableRoomState(int room_id)
{
    QSqlQuery q;
    q.prepare("SELECT current_cost FROM room_state WHERE room_id=:rid");
    q.bindValue(":rid",room_id);
    q.exec();
    double energy = q.value(0).toInt();
    return energy;
}

//------------------获取MainWindow实体属性<MasterState>,<DEFAULT_TEMP>-----------------------
void NetController::recvStateFromMainWindow(int val){
    this->MasterState = val;
}

void NetController::recvTempFromMainWindow(int val){
    this->DEFAULT_TEMP = val;
}

int NetController::getMinuteTo(QDateTime t1, QDateTime t2)
{
    int sec = t1.secsTo(t2);
    int minute = sec/60;
    return minute;
}

void NetController::sendPowerOffToSlave()
{
    for (QMap<int,TcpClientSocket*>::iterator it = room_list.begin();it != room_list.end();it++)
    {
        sendPowerOff(it.value());
    }
}

void NetController::sendPowerOnToSlave()
{
    for (QMap<int,TcpClientSocket*>::iterator it = room_list.begin();it != room_list.end();it++)
    {
        sendPowerOn(it.value());
    }
}

void NetController::recvWorkmodeFromMainWindow(int val){
    this->workmode = val;
}
