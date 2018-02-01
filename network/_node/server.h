#ifndef SERVER_H
#define SERVER_H

#include "node_global.h"
#include <QString>
#include <QTcpServer>
#include <QDebug>
#include "remoteclient.h"

class NODEHARED_EXPORT Server : public QTcpServer
{
    Q_OBJECT

private:
    const QString host = "localhost";
    const int port = 2397;

public:
    Server();
    void startServer();
    void incomingConnection(int socketDescriptor);

};

#endif // SERVER_H