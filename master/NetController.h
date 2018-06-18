#ifndef NETCONTROLLOR_H
#define NETCONTROLLOR_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QMap>
#include <QList>
#include <QTimer>
#include <QMutex>
#include "tcpclientsocket.h"
#include "constant.h"

class NetController : public QTcpServer
{
    Q_OBJECT
signals:
    void subMachineAskLogin();
    void sendAdminInfoToUi(bool );

public:
    explicit NetController(QObject *parent = 0);
    void send(QTcpSocket*,QJsonObject json);
    void sendReply(QTcpSocket*,int,int,int);
    //void startserver();
    void sendEnergyAndCost(QTcpSocket*,double energy,double cost);
    void sendReplyForState(QTcpSocket*,bool ack);
    void sendReplyForWindSupply(QTcpSocket*,bool ack);
    void sendReplyForStopWindSupply(QTcpSocket*,bool ack);
    void sendPowerOn(QTcpSocket*);
    void sendPowerOff(QTcpSocket*);
    void judgeLogin(int,QJsonObject obj);
    void judgeWindSupply(int,QJsonObject obj);
    void removeSlaveInfo(int,QJsonObject obj);
    void stopSlaveWind(int,QJsonObject obj);
    void modifySlaveTemp(int,QJsonObject obj);
    void startListening();
    void closeServer();

    bool loginSuccess(int room_id, QString user_id );
    void insertTableNetinfo(QJsonObject);
    //void checkAdminInfo(QString id, QString password);


private:
    quint16 BlockSize = 0;

    int no;//从机编号
    int port;//端口号
    QList<TcpClientSocket*> tcpClientSocketList;

private slots:
    //void ReadMessage();
    void ReadMessage(int,QJsonObject);

public slots:
    void slotDisconnected(int descriptor);

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // NETCONTROLLOR_H
