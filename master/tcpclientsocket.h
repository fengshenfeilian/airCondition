#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
//Tcp连接类
class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpClientSocket(QObject *parent = 0);
    int no; //指明这是第几个连接
    int blocksize;


signals:
    void disconnected(int);
    void sendToServer(int no, QJsonObject data);
protected slots:
    void dataReceived();   //收到报文，发给控制器
    void slotDisconnected();//连接断开时的操作
};

#endif // TCPCLIENTSOCKET_H
