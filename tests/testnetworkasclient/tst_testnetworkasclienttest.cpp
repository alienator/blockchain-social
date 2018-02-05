#include <QString>
#include <QtTest>
#include <QTcpSocket>
#include <QDataStream>

class TestnetworkasclientTest : public QObject
{
    Q_OBJECT

public:
    TestnetworkasclientTest();

private Q_SLOTS:
    void testCase1();
};

TestnetworkasclientTest::TestnetworkasclientTest()
{
}

void TestnetworkasclientTest::testCase1()
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->connectToHost("192.168.1.30", 2397);

    if (socket->waitForConnected()) {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);

        QByteArray c;
        c.append(QByteArray("tipo"));
        c.append(QByteArray("peyload_tipo"));

        out.setVersion(QDataStream::Qt_5_10);
        out << QString("comando1");
        out << c;

        socket->write(block);
        socket->flush();
        socket->waitForBytesWritten();
        //socket->disconnectFromHost();
    }

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestnetworkasclientTest)

#include "tst_testnetworkasclienttest.moc"
