#include <QString>
#include <QtTest>

#include "../../core/block/blockchain.h"
#include "../../core/block/genesis.h"

class TestgeensisTest : public QObject
{
    Q_OBJECT

public:
    TestgeensisTest();

private Q_SLOTS:
    void testCreate();
};

TestgeensisTest::TestgeensisTest()
{
}

void TestgeensisTest::testCreate()
{
    BlockChain *bc = BlockChain::getInstance();
    bc->createGenesis();

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestgeensisTest)

#include "tst_testgeensistest.moc"
