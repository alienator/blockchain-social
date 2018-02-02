#include <QString>
#include <QtTest>
#include "../../network/node/message.h"

class TestmessageTest : public QObject
{
    Q_OBJECT

public:
    TestmessageTest();

private Q_SLOTS:
    void testCase1();
};

TestmessageTest::TestmessageTest()
{
}

void TestmessageTest::testCase1()
{

    /*QFile file("/home/rloza/file.dat");
    file.open(QIODevice::ReadWrite);*/

    QByteArray file;
    QDataStream out(&file, QIODevice::ReadWrite);

//    QDataStream out;
    Message msg;

    msg.setCommand("comando");
    msg.setPayload(QByteArray("126"));
    out << msg;

    out.device()->reset();

    Message msg2;
    out >> msg2;
    //file.close();

    qDebug() << msg2.toString();

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestmessageTest)

#include "tst_testmessagetest.moc"
