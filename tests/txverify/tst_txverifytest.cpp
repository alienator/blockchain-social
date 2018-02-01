#include <QString>
#include <QtTest>
#include <QDebug>

#include "../../core/block/transaction/registertransaction.h"

class TxverifyTest : public QObject
{
    Q_OBJECT

public:
    TxverifyTest();

private Q_SLOTS:
    void testVerify();
};

TxverifyTest::TxverifyTest()
{
}

void TxverifyTest::testVerify()
{
    RegisterTransaction *tx = new RegisterTransaction(QByteArray("xxxx"), 0, "NN");
    qDebug() << tx->verify();

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TxverifyTest)

#include "tst_txverifytest.moc"
