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
        quint32 state = credits.value(i).getState();
        if (state == CHANGE
            || state == UNSPENT) {
            balance += credits.value(i).getValue();
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
    QList<Tx> inputs;
    for (int i = 0; i < credits.size(); i++) {
        quint32 state = credits.value(i).getState();
        if (state != UNSPENT &&
            state != CHANGE) {
            continue;
        }

        inputValue += credits.value(i).getValue();
        tx->addInput(new TxInput(QByteArray::fromHex(credits.value(i).getHash().toUtf8()), i));
        inputs.append(credits.value(i));

        if (inputValue >= value) {
                break;
        }
    }

    QByteArray address = QByteArray::fromHex(target.toLatin1());
    TxOutput *out = new TxOutput(address, value);
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

    //update inputs state
    for (int i = 0; i < inputs.size(); i++) {
        quint32 state = inputs.value(i).getState();
        if (state == CHANGE) {
            mongo->updateState(inputs.value(i).getHash(), CHANGE_SPENT);
        }
        else {
            mongo->updateState(inputs.value(i).getHash(), SPENT);
        }
    }

    //save wallet db
    mongo->saveTransaction(tx->getHash().toHex().toStdString().c_str(), value, SENDED);

    //calculate change
    if (inputValue > value) {
        TransferenceTransaction *txchange = new TransferenceTransaction();
        TxOutput *change;
        change = new TxOutput(QByteArray::fromHex(pubKey.toUtf8()), (inputValue - value));
        txchange->addOutput(change);
        txchange->addInput(new TxInput(tx->getHash(), 0));
        txchange->setHash(txchange->calculateHash());

        Block blockchange;
        blockchange.addTransaction(txchange);

        Header headerchange;
        headerchange.setIndex(bc->getLastHeader().getIndex() + 1);
        headerchange.setMerkleRoot(blockchange.generateMerkleRoot());
        headerchange.setPreviousHash(bc->getLastHeader().getHash());
        headerchange.setTimestamp(QDateTime::currentMSecsSinceEpoch());
        headerchange.setHash(headerchange.calculateHash());

        blockchange.addHeader(headerchange);

        bc->saveBlock(blockchange);

        mongo->saveTransaction(txchange->getHash().toHex().toStdString().c_str(), (inputValue - value), CHANGE);
    }

    loadTransactions();
}
