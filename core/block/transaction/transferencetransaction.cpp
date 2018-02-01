#include "transferencetransaction.h"
#include <QCryptographicHash>
#include <QDebug>

TransferenceTransaction::TransferenceTransaction(QByteArray source, QByteArray target, double amount)
{
    this->source = source;
    this->target = target;
    this->amount = amount;
    this->hash = calculateHash();
}

QByteArray TransferenceTransaction::getSource()
{
    return source;
}

QByteArray TransferenceTransaction::getTarget()
{
    return target;
}

double TransferenceTransaction::getAmount()
{
    return amount;
}

QByteArray TransferenceTransaction::calculateHash()
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(this->type);
    hash.addData(this->source);
    hash.addData(this->target);
    hash.addData(QByteArray::number(this->amount));

    return hash.result();
}

void TransferenceTransaction::debug()
{
    qDebug() << "TransferenceTransaction["
             << "hash=" << this->hash.toHex()
             << ", type=" << this->type
             << ", source=" << this->source.toHex()
             << ", target=" << this->target.toHex()
             << ", amount=" << this->amount
             << "]";
}

quint32 TransferenceTransaction::getSize()
{
    quint32 size = 0;
    size += 3; //type
    size += source.size();
    size += target.size();
    size += 8;

    return size;
}

