#include "remoteclient.h"

RemoteClient::RemoteClient(QObject *parent, int socketDescriptor)
    : QObject(parent)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,
            SIGNAL(readyRead()),
            this,
            SLOT(read())
            );

    pool = new QThreadPool(this);
    pool->setMaxThreadCount(10);
}

void RemoteClient::read()
{
    qDebug() << "Process Message and Decide who Payload loads";
}

void RemoteClient::write(QByteArray buffer)
{

}
