#include <QString>
#include <QtTest>
#include "../../core/block/transaction/transferencetransaction.h"
#include "../../core/block/blockchain.h"

class TranstransactionTest : public QObject
{
    Q_OBJECT

public:
    TranstransactionTest();

private Q_SLOTS:
    void testCreate();
    void testSaveTx();
};

TranstransactionTest::TranstransactionTest()
{
}

void TranstransactionTest::testCreate()
{
    QByteArray source;
    QByteArray target;
    double amount = 2.23;

    //0
    source = QByteArray::fromHex(QString("5feceb66ffc86f38d952786c6d696c79c2dbc239dd4e91b46729d73a27fb57e9").toLatin1());

    //1
    target = QByteArray::fromHex(QString("6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b").toLatin1());

    TxOutput *out = new TxOutput(source, amount);

    TransferenceTransaction *tx = new TransferenceTransaction();
    tx->addOutput(out);
    tx->setHash(tx->calculateHash());

    tx->debug();

    QVERIFY2(true, "Failure");
}

void TranstransactionTest::testSaveTx()
{
    BlockChain *bc = BlockChain::getInstance();
    bc->createGenesis();

    Block b;
    Header h;

    QByteArray source;
    QByteArray target;
    double amount = 2.23;

    //0
    source = QByteArray::fromHex(QString("5feceb66ffc86f38d952786c6d696c79c2dbc239dd4e91b46729d73a27fb57e9").toLatin1());

    //1
    target = QByteArray::fromHex(QString("6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b").toLatin1());

    TxOutput *out = new TxOutput(target, amount);

    TransferenceTransaction *tx = new TransferenceTransaction();
    tx->addOutput(out);
    tx->setHash(tx->calculateHash());

    b.addTransaction(tx);

    h.setIndex(bc->getLastHeader().getIndex() + 1);
    h.setPreviousHash(bc->getLastHeader().getHash());
    QDateTime timestamp = QDateTime::currentDateTime();
    h.setTimestamp(timestamp.toUTC().toMSecsSinceEpoch());
    h.setMerkleRoot(b.generateMerkleRoot());
    h.setHash(h.calculateHash());

    b.addHeader(h);
b.debug();
    bc->saveBlock(b);

}

QTEST_APPLESS_MAIN(TranstransactionTest)

#include "tst_transtransactiontest.moc"
