#include "NetController.h"
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
//发送登陆请求回复
void NetController::sendReply( int reply,int workmode,int worktemp){
    QJsonObject rfl;
    rfl.insert("Type","ReplyForLogin");
    rfl.insert("Reply",reply);
    rfl.insert("WorkMode",workmode);
    rfl.insert("WorkTemperature",worktemp);
    send(rfl);
}
//发送能耗和费用信息
void NetController::sendEnergyAndCost( double energy,double cost)
{
    QJsonObject eac;
    eac.insert("Type","EnergyAndCost");
    eac.insert("Energy",energy);
    eac.insert("Cost",cost);
    send(eac);
}
//发送接收状态信息回复
void NetController::sendReplyForState( bool ack){
    QJsonObject rfs;
    rfs.insert("Type","ReplyForState");
    rfs.insert("Ack",ack);
    send(rfs);
}
//发送请求送风回复
void NetController::sendReplyForWindSupply(bool ack){
    QJsonObject rfws;
    rfws.insert("Type","ReplyForWindSupply");
    rfws.insert("Ack",ack);
    send(rfws);
}
//发送停止送风回复
void NetController::sendReplyForStopWindSupply(bool ack){
    QJsonObject rfs;
    rfs.insert("Type","ReplyForStopWindSupply");
    rfs.insert("Ack",ack);
    send(rfs);
}
//发送开机信号
void NetController::sendPowerOn()
{
    QJsonObject po;
    po.insert("Type","PowerOn");
    send(po);
}
//发送关机信号
void NetController::sendPowerOff(){
    QJsonObject pof;
    pof.insert("Type","PowerOff");
    send(pof);
}
//服务器监视socket
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
           QString type = obj.value("Type").toString();
           //从机请求登陆
           if(type == "AskLogin"){
               //进入判断函数，判断后进行后续操作
               judgeLogin(obj);
               //sendReply(0,0,25);
           }
           else if(type == "AskWindSupply"){
               //收到送风请求
               judgeWindSupply(obj);
                //sendReplyForWindSupply(true);
           }
           else if(type == "StopWindSupply"){
               //停止送风
               stopSlaveWind(obj);
               sendReplyForStopWindSupply(true);
           }
           else if(type == "State")
           {
               //维护从控表当前温度信息
               modifySlaveTemp(obj);
               sendReplyForState(true);
           }
           else if(type == "AskLogout")
           {

               //删除roomid_close的信息表
               removeSlaveInfo(obj);
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
           BlockSize = 0;
    }

}
//子模块：发送JSON
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

void NetController::judgeLogin(QJsonObject obj)
{
    int roomid = obj.value("Room").toInt();
    QString user_id = obj.value("ID").toString();
    //登陆判断后续操作
}

void NetController::judgeWindSupply(QJsonObject obj){
    int roomid = obj.value("Room").toInt();
    int askTemp = obj.value("Temperature").toInt();
    int askWindSpeed = obj.value("WindSpeed").toInt();
    int windType = obj.value("WindType").toInt();
    //送风请求后续操作
}

void NetController::removeSlaveInfo(QJsonObject obj){
    int roomid = obj.value("Room").toInt();
    //从机关机
}

void NetController::stopSlaveWind(QJsonObject obj){
    int roomid = obj.value("Room").toInt();
    //从机停风
}

void NetController::modifySlaveTemp(QJsonObject obj){
    int roomid = obj.value("Room").toInt();
    int current_temp = obj.value("Temperature").toInt();
    //从机的当前温度
}
