#ifndef TRANSFERENCETRANSACTION_H
#define TRANSFERENCETRANSACTION_H

#include "atransaction.h"

class TransferenceTransaction : public ATransaction
{
protected:
    QByteArray source;
    QByteArray target;
    double amount;
    QByteArray hash;
public:
    TransferenceTransaction(QByteArray source,
                            QByteArray target, double amount);
    QByteArray getSource();
    QByteArray getTarget();
    double getAmount();
    bool verify();
    QByteArray calculateHash();
    quint32 getSize();
    void debug();
};

#endif // TRANSFERENCETRANSACTION_H
