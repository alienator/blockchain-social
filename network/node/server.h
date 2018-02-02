#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QTcpServer>
#include <QDebug>
#include "remoteclient.h"

class Server : public QTcpServer
{
    Q_OBJECT

private:
    const QString host = "192.168.1.30";
    const int port = 2397;

public:
    Server();
    void startServer();

protected:
    void incomingConnection(qintptr handle);

};

#endif // SERVER_H
