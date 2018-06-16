#ifndef NETCONTROLLOR_H
#define NETCONTROLLOR_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QMap>
#include <QList>
#include <QTimer>
#include "constant.h"

class NetController : public QObject
{
    Q_OBJECT
signals:
    void subMachineAskLogin();

public:
    explicit NetController(QObject *parent = 0);
    void send(QJsonObject json);
    void sendReply(int,int,int);
    void startserver();
    void sendEnergyAndCost(double energy,double cost);
    void sendReplyForState(bool ack);
    void sendReplyForWindSupply(bool ack);
    void sendReplyForStopWindSupply(bool ack);
    void sendPowerOn();
    void sendPowerOff();
    void judgeLogin(QJsonObject obj);
    void judgeWindSupply(QJsonObject obj);
    void removeSlaveInfo(QJsonObject obj);
    void stopSlaveWind(QJsonObject obj);
    void modifySlaveTemp(QJsonObject obj);

private:
    QTcpServer *mainserver;
    quint16 BlockSize = 0;
    QTcpSocket *tsock;
    QList<QTcpSocket*> tcpList;

private slots:
    void ReadMessage();
    void rr();
};

#endif // NETCONTROLLOR_H
