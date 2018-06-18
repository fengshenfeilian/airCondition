#include "tcpclientsocket.h"
//#include<QTcpSocket>
#include<QDataStream>
#include <QDebug>
TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(this, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
}

void TcpClientSocket::dataReceived()
{
    qDebug()<<"缓冲区现有字节"<<(bytesAvailable());
    //按照Demo改
    QDataStream in(this);
    QString Message;
    in.setVersion(QDataStream::Qt_5_5);
    quint16 size = 0;
    if(size == 0)
    {
        if(this->bytesAvailable() < sizeof(quint16))
            return;
        in >> size;
    }
    if(size == 0xFFFF) return;
    if(this->bytesAvailable() < size)
    {
        qDebug() << size << endl;
        return;
    }
    in >> Message;
    qDebug() << Message;
    QByteArray string1 = Message.toUtf8();
    QJsonDocument ParseDocument = QJsonDocument::fromJson(string1);
    QJsonObject obj = ParseDocument.object();

    qDebug() << obj << endl;
    emit sendToServer(this->no,obj);

}

void TcpClientSocket::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}

