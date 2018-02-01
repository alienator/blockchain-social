#include "registertransaction.h"
#include <QCryptographicHash>

#include <QDebug>

RegisterTransaction::RegisterTransaction(QByteArray owner, double amount, QString name)
{
    strcpy(this->type, "REG");
    this->owner = owner;
    this->amount = amount;
    this->name = name;
    this->hash = this->calculateHash();
}

QByteArray RegisterTransaction::getOwner()
{
    return owner;
}

double RegisterTransaction::getAmount()
{
    return amount;
}

QString RegisterTransaction::getName()
{
    return name;
}

quint32 RegisterTransaction::getSize()
{
    quint32 size = 0;
    size += 3; //type
    size += owner.size();
    size += 8;
    size += QByteArray::fromStdString(name.toStdString()).size();

    return size;
}

QByteArray RegisterTransaction::calculateHash()
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(this->type);
    hash.addData(QByteArray::number(this->amount));
    hash.addData(this->owner);

    return hash.result();
}

void RegisterTransaction::debug()
{
    qDebug() << "RegisterTransaction["
             << "hash=" << this->hash.toHex()
             << ", type=" << this->type
             << ", amount=" << this->amount
             << ", owner=" << this->owner.toHex()
             << ", name=" << this->name
             << "]";
}


