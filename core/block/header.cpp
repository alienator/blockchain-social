#include "header.h"
#include <QString>
#include <QCryptographicHash>

QByteArray Header::calculateHash()
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(QByteArray::number(this->index));
    hash.addData(QByteArray::number(this->timestamp));
    hash.addData(this->previous_hash);
    hash.addData(this->merkle_root);

    return hash.result();
}

quint32 Header::getSize()
{
    int size = 0;
    size += 4; //index
    size += 8; //timestamp
    size += previous_hash.size();
    size += merkle_root.size();

    return size;
}

bool Header::verify()
{
    return false;
}

void Header::setHash(QByteArray hash)
{
    this->hash = hash;
}

quint32 Header::getIndex()
{
    return index;
}

void Header::setIndex(quint32 index)
{
    this->index = index;
}

void Header::setPreviousHash(QByteArray previous_hash)
{
    this->previous_hash = previous_hash;
}

QByteArray Header::getPreviousHash()
{
    return previous_hash;
}

void Header::setMerkleRoot(QByteArray merkle_root)
{
    this->merkle_root = merkle_root;
}

QByteArray Header::getMerkleRoot()
{
    return merkle_root;
}

void Header::setTimestamp(qint64 timestamp)
{
    this->timestamp = timestamp;
}

qint64 Header::getTimestamp()
{
    return timestamp;
}

void Header::debug()
{
    qDebug() << "Header["
             << "hash=" << this->hash.toHex()
             << ", index=" << this->index
             << ", previous_hash=" << this->previous_hash.toHex()
             << ", merkle_root=" << this->merkle_root.toHex()
             << ", timestamp=" << this->timestamp
             << "]";

}
