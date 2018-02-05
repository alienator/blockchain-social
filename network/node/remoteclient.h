#ifndef REMOTECLIENT_H
#define REMOTECLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QThreadPool>
#include "message.h"

class RemoteClient : public QObject
{
    Q_OBJECT
public:
    explicit RemoteClient(QObject *parent = nullptr, int socketDescriptor = 0);

signals:
    void complete(QByteArray buffer);

private:
    QTcpSocket *socket;
    QThreadPool *pool;
    QDataStream in;

public slots:
    void read();
    void write(QByteArray buffer);
};

#endif // REMOTECLIENT_H
