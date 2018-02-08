#ifndef WALLET_H
#define WALLET_H

#include <QDebug>
#include <QDateTime>
#include <QObject>

#include "../core/block/blockchain.h"
#include "../core/block/transaction/transferencetransaction.h"
#include "tx.h"
#include "mongodb.h"

enum States {
    NEW_WALLET = 0,
    EXISTING_WALLET = 1,
};

enum TxState {
    UNSPENT = 0,
    SPENT = 1,
    LOCK = 2,
    CHANGE = 3,
    SENDED = 4,
    CHANGE_SPENT = 5
};

class Wallet : public QObject
{
    Q_OBJECT

public:
    Wallet();
    void init();
    QString getPubKey();
    double getBalance();
    QList<Block> getBlocks();

    QList<Tx> getCredits();
    QList<Tx> getDebits();
    QList<Tx> getUnspent();

    void send(QString target, double value);

private:
    States state;
    BlockChain *bc;
    const QString pubKey = "6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b";

    double balance;
    QList<Block> blocks;
    QList<Tx> credits;
    QList<Tx> debits;
    QList<Tx> unspent;

    void initTransaction();
    void loadTransactions();

signals:
    void updated(QList<Tx> txs);
};

#endif // WALLET_H
