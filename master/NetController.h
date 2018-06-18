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
#include "datastruct.h"

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
    void logoutSuccess(int no, QJsonObject obj);
    void insertTableNetinfo(QJsonObject obj, int objType);
    void processMessage(int no, QJsonObject obj);
    void updateTableRoomStateTup(QJsonObject obj, int sign);
    //void checkAdminInfo(QString id, QString password);


private:
    quint16 BlockSize = 0;

    int no;//从机编号
    int port;//端口号
    QList<TcpClientSocket*> tcpClientSocketList;

    QMap<int,TcpClientSocket*> room_list;
    QTimer* billTimer;

private slots:
    //void ReadMessage();
    void ReadMessage(int,QJsonObject);
    void sendBillToSlave();//---------------------------new

public slots:
    void slotDisconnected(int descriptor);

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // NETCONTROLLOR_H
