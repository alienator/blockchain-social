#include "block.h"

#include <QDebug>
#include <QCryptographicHash>

Block::Block()
{

}

void Block::addHeader(Header header)
{
    this->header = header;
}

void Block::addTransaction(ATransaction *transaction)
{
    transactions.append(transaction);
}

Header Block::getHeader()
{
    return header;
}

QVector<ATransaction *> Block::getTransactions()
{
    return transactions;
}

quint32 Block::getSize()
{
    quint32 size = 0;
    size += header.getSize();
    for (int i = 0; i < transactions.size(); i++) {
        ATransaction* tx = transactions.at(i);
        size += tx->getSize();
    }

    return size;
}

QByteArray Block::generateMerkleRoot()
{
    QVector<QByteArray> hashes;
    for (int i = 0; i < transactions.size(); i++) {
        ATransaction* tx = transactions.at(i);
        hashes.append(tx->getHash());
    }

    QByteArray root = parseTree(hashes);

    return root;
}

QByteArray Block::parseTree(QVector<QByteArray> hashes)
{
    int total = hashes.size();
    QVector<QByteArray> parsed;
    if (total == 1) {
        return hashes.at(0);
    }

    for (int j = 0; j < total; j++) {
        QByteArray left = hashes.at(j);
        QByteArray right = NULL;
        if ((j+1) == total && (total%2) != 0) {
            right = left;
        } else {
            right = hashes.at(++j);
        }

        QCryptographicHash hash(QCryptographicHash::Sha256);
        hash.addData(left);
        hash.addData(right);
        QByteArray branch = hash.result();
        parsed.append(branch);
    }

    if (parsed.size() > 1) {
        parseTree(parsed);
    }

    return parsed.at(0);
}

bool Block::verify()
{
    return false;
}

void Block::debug()
{
    qDebug() << "Block[";
    header.debug();
    for (int i = 0; i < transactions.size(); i++) {
        transactions.at(i)->debug();
    }
    qDebug() << "]";
}
