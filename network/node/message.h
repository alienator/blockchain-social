#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QDebug>
#include <QDataStream>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);

private:
    QString command;
    QByteArray payload;
    friend QDataStream &operator<<(QDataStream &, const Message &);
    friend QDataStream &operator>>(QDataStream &, Message &);

public:
    void setCommand(QString cmd);
    void setPayload(QByteArray payload);
    QString toString();

signals:

public slots:
};

#endif // MESSAGE_H
