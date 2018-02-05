#include "payload.h"

Payload::Payload()
{

}

QString Payload::toString()
{
    QString text;
    text.append("Payload[");
    text.append("type: " + type);
    text.append(", payload:" + payload);
    text.append("]");

    return text;
}

QDataStream &operator << (QDataStream &out, const Payload &payload)
{
    out << payload.type << payload.payload;
    return out;
}

QDataStream &operator >> (QDataStream &in, Payload &payload)
{
    in >> payload.type >> payload.payload;
    return in;
}
