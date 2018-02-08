#include "wallet.h"

Wallet::Wallet()
{        

}

void Wallet::init()
{
    bc = BlockChain::getInstance();

    loadTransactions();
    if (credits.size() == 0) {
        state = NEW_WALLET;
    }
    else {
        state = EXISTING_WALLET;
    }

    if (state == NEW_WALLET) {
        initTransaction();
    }
}

void Wallet::initTransaction()
{
    if (bc->getHeight() == 0) {
        bc->createGenesis();
    }

    QByteArray address = QByteArray::fromHex(pubKey.toLatin1());
    double value = 100;
    TxOutput *out = new TxOutput(address, value);
    TransferenceTransaction *tx = new TransferenceTransaction();
    tx->addOutput(out);
    tx->setHash(tx->calculateHash());

    Block block;
    block.addTransaction(tx);

    Header header;
    header.setIndex(bc->getLastHeader().getIndex() + 1);
    header.setMerkleRoot(block.generateMerkleRoot());
    header.setPreviousHash(bc->getLastHeader().getHash());
    header.setTimestamp(QDateTime::currentMSecsSinceEpoch());
    header.setHash(header.calculateHash());

    block.addHeader(header);

    bc->saveBlock(block);

    ThisWallet::MongoDb *mongo = new ThisWallet::MongoDb();
    mongo->saveTransaction(tx->getHash().toHex().toStdString().c_str(), value, UNSPENT);

    loadTransactions();
}

QString Wallet::getPubKey()
{
    return pubKey;
}

double Wallet::getBalance()
{
    return balance;
}

/*void Wallet::xxloadTransactions()
{
    blocks = bc->outputs(pubKey);
    balance = 0;

    for (int j = 0; j < blocks.size(); j++) {
        QVector<ATransaction *>txs = blocks.value(j).getTransactions();
        for (int i = 0; i < txs.size(); i++) {
            TransferenceTransaction *tx = dynamic_cast<TransferenceTransaction *>(txs.value(i));
            QList<TxOutput *> outs = tx->getOutputs();
            for (int k = 0; k < outs.size(); k++) {
                if (QString::fromUtf8(outs.value(k)->getAddress().toHex()) == pubKey) {
                    balance += tx->getOutputs().value(0)->getValue();
                }
            }
        }
    }
}*/

void Wallet::loadTransactions()
{
    ThisWallet::MongoDb *mongo = new ThisWallet::MongoDb();
    credits.clear();
    credits = mongo->loadCredits();

    //debits = mongo->loadDebits();
    //unspent = mongo->loadUnspent();

    //calculate balance
    balance = 0;
    for (int i = 0; i < credits.size(); i++) {
        if (credits.value(i).getState() == UNSPENT
                ||
                credits.value(i).getState() == SPENT) {
            balance += credits.value(i).getValue();
        }
        else if (credits.value(i).getState() == SENDED) {
            balance -= credits.value(i).getValue();
        }
    }

    emit updated(credits);
}

QList<Block> Wallet::getBlocks()
{
    return blocks;
}

QList<Tx> Wallet::getCredits()
{
    return credits;
}

void Wallet::send(QString target, double value)
{
    TransferenceTransaction *tx = new TransferenceTransaction();

    //calculate inputs ref
    double inputValue = 0;
    QList<QString> inputs;
    for (int i = 0; i < credits.size(); i++) {
        inputValue += credits.value(i).getValue();

        tx->addInput(new TxInput(QByteArray::fromHex(credits.value(i).getHash().toUtf8()), i));
        inputs.append(credits.value(i).getHash());

        if (inputValue >= value) {
                break;
        }
    }

    QByteArray address = QByteArray::fromHex(target.toLatin1());
    TxOutput *out = new TxOutput(address, value);
    tx->addOutput(out);

    //calculate cchange
    TxOutput *change;
    if (inputValue > value) {
        change = new TxOutput(QByteArray::fromHex(pubKey.toUtf8()), (inputValue - value));
        tx->addOutput(change);
    }

    tx->setHash(tx->calculateHash());

    Block block;
    block.addTransaction(tx);

    Header header;
    header.setIndex(bc->getLastHeader().getIndex() + 1);
    header.setMerkleRoot(block.generateMerkleRoot());
    header.setPreviousHash(bc->getLastHeader().getHash());
    header.setTimestamp(QDateTime::currentMSecsSinceEpoch());
    header.setHash(header.calculateHash());

    block.addHeader(header);

    bc->saveBlock(block);

    //save wallet db
    ThisWallet::MongoDb *mongo = new ThisWallet::MongoDb();
    mongo->saveTransaction(tx->getHash().toHex().toStdString().c_str(), value, SENDED);

    if (inputValue > value) {
        mongo->saveTransaction(tx->getHash().toHex().toStdString().c_str(), (inputValue - value), CHANGE);
    }

    //update inputs state
    for (int i = 0; i < inputs.size(); i++) {
        mongo->updateState(inputs.value(i), SPENT);
    }

    loadTransactions();
}
