#ifndef WALLET_H
#define WALLET_H

#include <QDebug>
#include <QDateTime>

#include "../core/block/blockchain.h"
#include "../core/block/transaction/transferencetransaction.h"

enum States {
    NEW_WALLET = 0,
    EXISTING_WALLET = 1,
};

class Wallet
{
public:
    Wallet();
    QString getPubKey();
    double getBalance();
    QList<Block> getBlocks();

private:
    States state;
    BlockChain *bc;
    const QString pubKey = "6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b";

    double balance;
    QList<Block> blocks;

    void initTransaction();
    void loadTransactions();
};

#endif // WALLET_H
