#include <QString>
#include <QtTest>
#include <QDebug>

#include "../../dbaccess/mongodb/mongodb.h"

class TxhistoryTest : public QObject
{
    Q_OBJECT

public:
    TxhistoryTest();

private Q_SLOTS:
    void testCase1();
};

TxhistoryTest::TxhistoryTest()
{
}

void TxhistoryTest::testCase1()
{
    QString address("5feceb66ffc86f38d952786c6d696c79c2dbc239dd4e91b46729d73a27fb57e9");
    MongoDB db;

    if (db.isConnected()) {
        QList<Block> bs = db.outputs(address);
        qDebug() << bs.size();
        for (int i = 0; i < bs.size(); i++) {
            bs.value(i).debug();
        }
    }
    else {
        qDebug() << "NO conectado";
    }


    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TxhistoryTest)

#include "tst_txhistorytest.moc"
