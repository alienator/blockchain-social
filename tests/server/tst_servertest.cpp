#include <QString>
#include <QtTest>

#include "../../network/node/server.h"

class ServerTest : public QObject
{
    Q_OBJECT

public:
    ServerTest();

private Q_SLOTS:
    void testHasTransaction();
};

ServerTest::ServerTest()
{
}

void ServerTest::testHasTransaction()
{
    Server s;
    s.startServer();

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ServerTest)

#include "tst_servertest.moc"
