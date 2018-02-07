#include "wallet.h"

Wallet::Wallet()
{        
    bc = BlockChain::getInstance();

    state = EXISTING_WALLET;

    if (state == NEW_WALLET) {
        initTransaction();
    }
    else {
        //initTransaction();
        loadTransactions();
    }
}

void Wallet::initTransaction()
{
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
}

QString Wallet::getPubKey()
{
    return pubKey;
}

double Wallet::getBalance()
{
    return balance;
}

void Wallet::loadTransactions()
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
}

QList<Block> Wallet::getBlocks()
{
    return blocks;
}
