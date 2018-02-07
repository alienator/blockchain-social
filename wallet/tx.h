#ifndef TX_H
#define TX_H

#include "../core/block/transaction/atransaction.h"
#include "../core/block/transaction/transferencetransaction.h"
#include <QString>

class Tx
{
private:
    QString target;
    double amount;

public:
    Tx(QString target, double amount);
    TransferenceTransaction buildTx();
};

#endif // TX_H
