#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <QString>
#include <QDebug>
#include <QByteArray>

class Payload
{
private:
    QString type;
    QByteArray payload;

    friend QDataStream &operator<<(QDataStream &, const Payload &);
    friend QDataStream &operator>>(QDataStream &, Payload &);

public:
    Payload();
    QString toString();
};

#endif // PAYLOAD_H
