#include <QString>
#include <QtTest>

#include "../../dbaccess/mongodb/mongodb.h"
#include "../../core/block/transaction/registertransaction.h"

class MongodbTest : public QObject
{
    Q_OBJECT

public:
    MongodbTest();

private Q_SLOTS:
    void testHasTransaction();
    void testGetlstHeader();
};

MongodbTest::MongodbTest()
{
}

void MongodbTest::testHasTransaction()
{
    MongoDB *db = new MongoDB;
    bool res = false;

    /*res = db->hasTransaction(QByteArray("7acffb8c634cafe4fd3257f99e46be97572a7575dc4bb39b6e230a2621dd686f"));

    QVERIFY(res);*/

    RegisterTransaction *r = new RegisterTransaction(QByteArray("own"), 50, "test2");
    //qDebug() << r->getHash().toHex();
    res = db->hasTransaction(r->getHash());
    QVERIFY(res);
}

void MongodbTest::testGetlstHeader()
{
    MongoDB *db = new MongoDB;
    Header h = db->getLastHeader();

    h.debug();
}

QTEST_APPLESS_MAIN(MongodbTest)

#include "tst_mongodbtest.moc"
