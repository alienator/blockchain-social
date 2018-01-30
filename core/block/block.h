#ifndef BLOCK_H
#define BLOCK_H

#include "header.h"
#include "transaction/atransaction.h"
#include "../iverifiable.h"
#include <QVector>

class Block : IVerifiable
{
protected:
   Header header;
   QVector<ATransaction*> transactions;
   QByteArray parseTree(QVector<QByteArray> hashes);
public:
    Block();
    quint32 getSize();
    bool verify();
    void addTransaction(ATransaction* transaction);
    void addHeader(Header header);
    QVector<ATransaction*> getTransactions();
    Header getHeader();
    void debug();
    QByteArray generateMerkleRoot();
};

#endif // BLOCK_H
