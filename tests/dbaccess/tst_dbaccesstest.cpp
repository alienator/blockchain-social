#include <QString>
#include <QtTest>

#include "../../dbaccess/dbaccess.h"
#include "../../core/block/transaction/registertransaction.h"
#include "../../core/block/blockchain.h"

class DbaccessTest : public QObject
{
    Q_OBJECT

public:
    DbaccessTest();

private Q_SLOTS:
    void testSave();
    void testGenesis();
};

DbaccessTest::DbaccessTest()
{
}

void DbaccessTest::testSave()
{
    RegisterTransaction *r = new RegisterTransaction(QByteArray("own"), 50, "test2");
    Header h;
    Block b;

    b.addTransaction(r);

    h.setIndex(100);
    h.setPreviousHash(QByteArray("0"));
    h.setTimestamp(123);
    h.setMerkleRoot(b.generateMerkleRoot());
    h.setHash(h.calculateHash());

    b.addHeader(h);

    Dbaccess *db = Dbaccess::getInstance();
    db->saveBlock(b);

    QVERIFY2(true, "Failure");
}

void DbaccessTest::testGenesis()
{
    BlockChain *bc = BlockChain::getInstance();
    bc->createGenesis();

    QVERIFY2(true, "Failure");
}


QTEST_APPLESS_MAIN(DbaccessTest)

#include "tst_dbaccesstest.moc"
