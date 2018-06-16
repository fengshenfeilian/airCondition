#include "netcontroller.h"
#include "constant.h"
NetController::NetController(QObject *parent) :
    QObject(parent)
{
    mainserver=new QTcpServer(this);
    //tsock = new QTcpSocket(this);
    connect(mainserver,&QTcpServer::newConnection,this,&NetController::rr);
    //qDebug() << "bind \n";
    startserver();
}

void NetController::startserver(){
    mainserver->listen(QHostAddress(QHostAddress::Any),6666);//set ip and port
}

void NetController::sendReply( int reply,int workmode,int worktemp){
    QJsonObject rfl;
    rfl.insert("Type","ReplyForLogin");
    rfl.insert("Reply",reply);
    rfl.insert("WorkMode",workmode);
    rfl.insert("WorkTemperature",worktemp);
    send(rfl);
}

void NetController::sendEnergyAndCost( double energy,double cost)
{
    QJsonObject eac;
    eac.insert("Type","EnergyAndCost");
    eac.insert("Energy",energy);
    eac.insert("Cost",cost);
    send(eac);
}

void NetController::sendReplyForState( bool ack){
    QJsonObject rfs;
    rfs.insert("Type","ReplyForState");
    rfs.insert("Ack",ack);
    send(rfs);
}

void NetController::sendReplyForWindSupply(bool ack){
    QJsonObject rfws;
    rfws.insert("Type","ReplyForWindSupply");
    rfws.insert("Ack",ack);
    send(rfws);
}

void NetController::sendReplyForStopWindSupply(bool ack){
    QJsonObject rfs;
    rfs.insert("Type","ReplyForStopWindSupply");
    rfs.insert("Ack",ack);
    send(rfs);
}

void NetController::sendPowerOn()
{
    QJsonObject po;
    po.insert("Type","PowerOn");
    send(po);
}

void NetController::sendPowerOff(){
    QJsonObject pof;
    pof.insert("Type","PowerOff");
    send(pof);
}

void NetController::rr()
{
    QTcpSocket *tsock1;
    //tcpList.push_back(mainserver->nextPendingConnection());
    tsock1 = mainserver->nextPendingConnection();
    tcpList.append(tsock1);
    //tcpList.append(tsock);
    connect(tsock1,&QTcpSocket::readyRead,this,&NetController::ReadMessage);
    //connect(tsock,&QTcpSocket::disconnected,tsock,QTcpSocket::deleteLater);
}

void NetController::ReadMessage(){

    for(int i = 0;i < tcpList.length();i++){
           BlockSize = 0;
           QDataStream in(tcpList.at(i));
           QString Message;
           in.setVersion(QDataStream::Qt_5_5);
           //qDebug() << tsock->readAll() << endl;
           if(BlockSize == 0){
               qDebug() << tcpList.at(i)->bytesAvailable() << endl;
               if(tcpList.at(i)->bytesAvailable() < sizeof(quint16)){
                  continue;
               }
               in >> BlockSize;

           }

           if(tcpList.at(i)->bytesAvailable() < BlockSize){
               continue;
           }
           in >> Message;
           QByteArray string1 = Message.toUtf8();
           QJsonDocument parseDoc = QJsonDocument::fromJson(string1);
           QJsonObject obj = parseDoc.object();
           qDebug() << obj << endl;
           QString type = obj.value("Type").toString();
           if(type == "AskLogin"){
               sendReply(0,0,25);
           }
           else if(type == "AskWindSupply"){
               qDebug() << "shoufeng\n";
                sendReplyForWindSupply(true);
           }
           else if(type == "StopWindSupply"){
               sendReplyForStopWindSupply(true);
           }
           else if(type == "State")
           {
               sendReplyForState(true);
           }
           else if(type == "AskLogout")
           {
               int roomid_close = obj.value("Room").toInt();
               //删除roomid_close的信息表
           }
           BlockSize = 0;
    }

}

void NetController::send(QJsonObject json)
{
    for(int i = 0;i < tcpList.length();i++){
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
    tcpList.at(i)->write(blocks);
    }
}


