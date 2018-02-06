#include "remoteclient.h"

RemoteClient::RemoteClient(QObject *parent, int socketDescriptor)
    : QObject(parent)
{
    socket = new QTcpSocket(this);    
    socket->setSocketDescriptor(socketDescriptor);

    in.setDevice(socket);
    in.setVersion(QDataStream::Qt_5_10);

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
    qDebug() << "Process Message and Decide which Payload loads";
    Message m;

    in.startTransaction();
    in >> m;

    if (!in.commitTransaction())
        return;

    m.debug();

    if (m.getCommand() == "getheight") {

        /*quint32 height = bc->getHeight();
        write(QByteArray::number(height));*/

    }
    /*else if (strcmp(m.getCommand(), "tx") == 0) {
        //LOAD txPayload THREAD
    }*/
}

void RemoteClient::write(QByteArray buffer)
{
    socket->write(buffer);
    socket->flush();
    socket->waitForBytesWritten();
}
