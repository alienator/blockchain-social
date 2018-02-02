#include "server.h"
#include <QDebug>
#include <QDateTime>
#include <QDate>

Server::Server()
{
}

void Server::startServer()
{
    QHostAddress address;
    address.setAddress(host);

    if (!this->listen(address, port)) {
        qWarning() << "Could not start server!"
                   << "at: " << host << " : " << port;
        return;
    }
    else
    {
        qDebug() << "Server running on: "
                 << this->serverAddress().toString()
                 << " : "
                 << this->serverPort();
    }
}

void Server::incomingConnection(qintptr handle)
{
    RemoteClient *client = new RemoteClient(this, handle);
}
