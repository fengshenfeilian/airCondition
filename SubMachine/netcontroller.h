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
    void checkOut();
    void centerPowerOff();
    void centerPowerOn();
    void freq(int);

public:
    explicit netController(QObject *parent = 0);
    QTcpSocket *tsock;


    //void sendCloseInfo(int roomid);
    bool preSendOpenInfo(int roomid,QString id);//return true when connected,false otherwise
    void send(QJsonObject json);
    void ReplyForPowerOff(int roomid);
    void ReplyForPowerOn(int roomid);
    void ReplyForEnergyAndCost(int roomid);
    void mySleep(int msec);


public slots:
    void AskLogin(int roomid,QString id);
    void AskWindSupply(int roomid,int targettemp,int windspeed,int mode);
    void setIsOpen(bool m);
    void AskLogout(int roomid);
    void State(int roomid,int temp);
    void StopWindSupply(int roomid);


private:
    quint16 BlockSize;
    int pendingroomid;//used to restore roomid temporaily

    bool isopen;

private slots:
    void ReadMessage();
    void lostconnect();
};

#endif // NETCONTROLLER_H
