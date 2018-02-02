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

QString Message::toString()
{
    QString string;
    string.append("Message[");
    string.append("command: " + command);
    string.append(", payload: " + payload);
    string.append("]");

    return string;
}

QDataStream &operator << (QDataStream &out, const Message &msg)
{
    out << msg.command << msg.payload;
    return out;
}

QDataStream &operator >> (QDataStream &in, Message &msg)
{
    in >> msg.command >> msg.payload;
    return in;
}
