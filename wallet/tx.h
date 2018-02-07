#ifndef TX_H
#define TX_H

#include "../core/block/transaction/transferencetransaction.h"
#include <QString>

class Tx
{
private:
    double balance;

public:
    Tx();
    double getBalance();
};

#endif // TX_H
