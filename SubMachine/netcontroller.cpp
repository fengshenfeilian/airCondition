#include "netcontroller.h"
#include "constants.h"
#include <QDebug>

netController::netController(QObject *parent) :
    QObject(parent)
{
    BlockSize = 0;
    isopen = true;
//    tsock=new QTcpSocket(this);
    tsock = sock;
    connect(tsock,SIGNAL(readyRead()),this,SLOT(ReadMessage()));
    connect(tsock,&QAbstractSocket::disconnected,this,&netController::lostconnect);
    tsock->connectToHost(IP,PORT);
}

void netController::send(QJsonObject json)
{
    if(isopen){
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
        sock->write(blocks);
        tsock->waitForBytesWritten(500);
//        qDebug() << json.value("Type") << endl;
    }
//        qDebug() << "从机处于关机/待机状态..." << endl;
}

//发送送风请求
void netController::AskWindSupply(int roomid,int targettemp,int windspeed,int mode){
    if(tsock->isOpen()){        
        QJsonObject swr;
        swr.insert("Type","AskWindSupply");
        swr.insert("Room",roomid);
        swr.insert("Temperature",targettemp);
        swr.insert("WindSpeed",windspeed);
        swr.insert("WindType",mode);
        send(swr);
//        qDebug() << "发出送风请求" << endl;
    }
}
//停止送风
void netController::StopWindSupply(int roomid){
    if(tsock->isOpen()){
        QJsonObject srt;
        srt.insert("Type","StopWindSupply");
        srt.insert("Room",roomid);
        send(srt);
    }
}
//登陆请求
void netController::AskLogin(int roomid,QString id){
    if(tsock->isOpen()){
        QJsonObject al;
        al.insert("Type","AskLogin");
        al.insert("Room",roomid);
        al.insert("ID",id);
        send(al);
    }
}
//连接主机
bool netController::preSendOpenInfo(int roomid,QString id){
    pendingroomid=roomid;
//    qDebug() << &tsock;
    if(tsock->state()!=QAbstractSocket::ConnectedState){
//        tsock->connectToHost(QHostAddress(IP),PORT);//set host ip and port
        if(tsock->waitForConnected(3000)==true){
            AskLogin(roomid,id);
        }
        else{
            return false;
        }
    }
    else{
        AskLogin(roomid,id);
    }
    return true;
}
//注销请求
void netController::AskLogout(int roomid){
    if(tsock->isOpen()){
        QJsonObject al;
        al.insert("Type","AskLogout");
        al.insert("Room",roomid);
        send(al);
//        mySleep(1000);
//        qDebug() << al;
    }
}
//状态信息
void netController::State(int roomid,int temp){
    if(tsock->isOpen()){
        QJsonObject al;
        al.insert("Room",roomid);
        al.insert("Type","State");
        al.insert("Temperature",temp);
        send(al);
    }
}

//费用接受回复
void netController::ReplyForEnergyAndCost(int roomid){
    if(tsock->isOpen()){
        QJsonObject al;
        al.insert("Type","ReplyForEnergyAndCost");
        al.insert("ack",true);
        send(al);
    }
}

//开机回复
void netController::ReplyForPowerOn(int roomid){
    if(tsock->isOpen()){
        QJsonObject al;
        al.insert("Type","ReplyForPowerOn");
        al.insert("ack",true);
        send(al);
    }
}

//关机回复
void netController::ReplyForPowerOff(int roomid){
    if(tsock->isOpen()){
        QJsonObject al;
        al.insert("Type","ReplyForPowerOff");
        al.insert("ack",true);
        send(al);
    }
}
void netController::ReadMessage(){
   QDataStream in(tsock);
   QString Message;
   in.setVersion(QDataStream::Qt_5_5);
//   qDebug() << "Blocksize:" << BlockSize << endl;
   if(BlockSize == 0){
       if(tsock->bytesAvailable() < sizeof(quint16)){
           return;
       }
       in >> BlockSize;
   }

   if(tsock->bytesAvailable() < BlockSize){
       return ;
   }
   in >> Message;
   QByteArray string1 = Message.toUtf8();
   QJsonDocument parseDoc = QJsonDocument::fromJson(string1);
   QJsonObject obj = parseDoc.object();
   qDebug() << obj;
   QString type;
   if(obj.contains("Type")){
        type = obj.value("Type").toString();
   }
//   qDebug() <<"recv:"<< type << endl;
   if(type == "EnergyAndCost"){
       emit energyAndCost(obj);
   }
   else if(type == "ReplyForLogin"){
       emit recvOpenAck(obj);
   }
   else if(type == "ReplyForWindSupply")
   {
       emit recvWind(obj);
   }
   else if(type == "ReplyForStopWindSupply")
   {
       emit stopWind(obj);
   }
   else if(type == "PowerOff")
   {
       emit centerPowerOff();
   }
   else if(type == "PowerOn")
   {
//       QJsonObject obj_temp;
       emit centerPowerOn();
   }
   BlockSize = 0;
}

void netController::lostconnect(){
    emit checkOut();
}

void netController::setIsOpen(bool m){
    isopen = m;
}

void netController::mySleep(int msec) //-----------------------------------------------------------------------------edit by marco
{
    QTime rtime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<rtime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

