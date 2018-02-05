#include "message.h"

Message::Message(QObject *parent) : QObject(parent)
{

}

void Message::setCommand(QString cmd)
{
    this->command = cmd;
}

void Message::setPayload(QByteArray payload)
{
    this->payload = payload;
}

void Message::debug()
{
    QByteArray pay;
    qDebug() << "Message["
             << "command: " << command
             << ", payload: " << payload
             << "]";

}

void Message::parsePayload()
{
    QDataStream strem(&this->payload, QIODevice::ReadOnly);
    QString type;
    qDebug() << type;
}

QDataStream &operator << (QDataStream &out, const Message &msg)
{
    out << msg.command << msg.payload;
    return out;
}

QDataStream &operator >> (QDataStream &in, Message &msg)
{
    QByteArray cmd;

    in >> cmd >> msg.payload;
    msg.command = QString(cmd);

    return in;
}
