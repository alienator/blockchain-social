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

    QString a = "6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b";
    QByteArray b;
    b = QByteArray::fromHex(a.toUtf8());

    QString c;
    c = QString::fromUtf8(b.toHex());

    qDebug() << a;
    qDebug() << b;
    qDebug() << c;

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TxverifyTest)

#include "tst_txverifytest.moc"
