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
    void testGetHeight();

private slots:
    void read();

private:
    QTcpSocket *socket;
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

void TestnetworkasclientTest::testGetHeight()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.1.30", 2397);

    if (socket->waitForConnected()) {
        QByteArray cmd;
        QByteArray pay;
        QDataStream wcmd(&cmd, QIODevice::WriteOnly);

        wcmd << "getheight";
        wcmd << pay;

        connect(socket,
                SIGNAL(readyRead()),
                this,
                SLOT(read())
                );

        socket->write(cmd);
        socket->flush();
        socket->waitForBytesWritten();
    }

    QVERIFY2(true, "Failure");
}

void TestnetworkasclientTest::read()
{
    quint32 response;
    QDataStream stream;
    stream.setDevice(socket);
    stream.startTransaction();

    stream >> response;

    if (!stream.commitTransaction()) {
        return;
    }

    qDebug() << response;
}

QTEST_APPLESS_MAIN(TestnetworkasclientTest)

#include "tst_testnetworkasclienttest.moc"
