#ifndef NETCONTROLLER_H
#define NETCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QtNetwork/QTcpSocket>
#include <QChar>
#include "constants.h"
#include <QDataStream>
#include <QHostAddress>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
class netController : public QObject
{
    Q_OBJECT
signals:
    void recvOpenAck(QJsonObject obj);
    void recvWind(QJsonObject obj);
    void energyAndCost(QJsonObject obj);
    void stopWind(QJsonObject oj);
//    void compelCLose();
    void centerPowerOff();
    void centerPowerOn(QJsonObject);
public:
    explicit netController(QObject *parent = 0);
    QTcpSocket *tsock;
    void AskWindSupply(int roomid,int targettemp,int windspeed,int mode);
    void StopWindSupply(int roomid);
    //void sendCloseInfo(int roomid);
    bool preSendOpenInfo(int roomid,QString id);//return true when connected,false otherwise
    void send(QJsonObject json);
    void ReplyForPowerOff(int roomid);
    void ReplyForPowerOn(int roomid);
    void ReplyForEnergyAndCost(int roomid);
    void State(int roomid,int temp);
    void AskLogout(int roomid);
    void AskLogin(int roomid,QString id);
    void setIsOpen(bool m);
    void connectIP();

private:
    quint16 BlockSize;
    int pendingroomid;//used to restore roomid temporaily

    bool isopen;

private slots:
    void ReadMessage();
    void lostconnect();
};

#endif // NETCONTROLLER_H
