#include "NetController.h"
#include "constant.h"
#include "datastruct.h"
#include "tcpclientsocket.h"

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

void NetController::sendBillToSlave()
{
    for (QMap<int,TcpClientSocket*>::iterator it = room_list.begin();it != room_list.end();it++)
    {
        int roomid = it.key();
        //查找到roomid对应的energy和cost
        double energy = 0.0;
        double cost = 0.0;
        energy += 1.0;
        cost += 1.0;
        sendEnergyAndCost(it.value(),energy,cost);
    }
}

void NetController::ReadMessage(int no,QJsonObject obj)
{
            qDebug() << "readmessage" << endl;
           QString type = obj.value("Type").toString();
           //从机请求登陆
           if(type == "AskLogin"){
               //进入判断函数，判断后进行后续操作
               judgeLogin(no,obj);
               //sendReply(0,0,25);
           }
           else if(type == "AskWindSupply"){
               //收到送风请求
               judgeWindSupply(no,obj);
                //sendReplyForWindSupply(true);
           }
           else if(type == "StopWindSupply"){
               //停止送风
               stopSlaveWind(no,obj);
               //sendReplyForStopWindSupply(true);
           }
           else if(type == "State")
           {
               //维护从控表当前温度信息
               modifySlaveTemp(no,obj);
               //sendReplyForState(no,true);
           }
           else if(type == "AskLogout")
           {

               //删除roomid_close的信息表
               removeSlaveInfo(no,obj);
           }
           else if(type == "ReplyForEnergyAndCost")
           {
               //不需要操作
           }
           else if(type == "ReplyForPowerOn")
           {
               //不需要操作
           }
           else if(type == "ReplyForPoserOff")
           {
               //不需要操作
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

void NetController::judgeLogin(int no,QJsonObject obj)
{
    int id = obj.value("Room").toInt();
    QString user_id = obj.value("ID").toString();
    //if登陆成功
    TcpClientSocket* tcpClientSocket;
    int index;
    for(int i = 0; i < tcpClientSocketList.count(); i++){
        tcpClientSocket = tcpClientSocketList.at(i);
        if(tcpClientSocket->no == no){
            index = i;
            break;
        }
    }
    TcpClientSocket* broad_tcp = tcpClientSocket;
    room_list.insert(id,broad_tcp);
    sendReply(tcpClientSocket,0,0,25);
    //登陆失败
    //sendReply(tcpClientSocket,1,0,25)
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

void NetController::removeSlaveInfo(int no,QJsonObject obj){
    int roomid = obj.value("Room").toInt();
    room_list.remove(roomid);
    //room_list[roomid].clear();
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

void NetController::startListening()
{
    no = 0;
    this->listen(QHostAddress::Any, port);
    this->billTimer = new QTimer();
    connect(billTimer, SIGNAL(timeout()), this, SLOT(sendBillToSlave()));

    this->billTimer->start(5000); //默认五秒发送一次账单信息
    /*this->refreshTimer = new QTimer();
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(sendStateQueryPackageToSlave()));
    this->refreshTimer->start((int)(refreshRate * 1000));*/
    //emit sendUpdateInfoToUi(refreshRate, workMode, status);
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
