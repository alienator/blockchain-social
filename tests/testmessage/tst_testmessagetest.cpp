#include <QString>
#include <QtTest>
#include "../../network/node/message.h"

class TestmessageTest : public QObject
{
    Q_OBJECT

public:
    TestmessageTest();

private Q_SLOTS:
    //void testCase1();
   // void testSerialize();
    void testSerialize2();
};

TestmessageTest::TestmessageTest()
{
}
/*
void TestmessageTest::testCase1()
{


    QByteArray file;
    QDataStream out(&file, QIODevice::ReadWrite);

    Message msg;

    msg.setCommand("comando");
    msg.setPayload(QByteArray("126"));
    out << msg;

    out.device()->reset();

    Message msg2;
    out >> msg2;

    qDebug() << msg2.toString();

    QVERIFY2(true, "Failure");
}

void TestmessageTest::testSerialize()
{
    QByteArray a;
    QByteArray b;
    QDataStream s(&a, QIODevice::WriteOnly);
    QDataStream t(&b, QIODevice::WriteOnly);

    s << "comando";

    t << (quint32)25;
    t << "mas texto";

    s << b;

    qDebug() << a;

    QByteArray g;
    QByteArray y;
    QDataStream h(&a, QIODevice::ReadOnly);
    //QDataStream j(&a, QIODevice::ReadOnly);

    h >> g;
    h >> y;

    qDebug() << g;
    qDebug() << y;

    QDataStream j(&y, QIODevice::ReadOnly);
    quint32 k;
    QByteArray l;
    j >> k;
    j >> l;

    qDebug() << k;
    qDebug() << QString(l);
}
*/
void TestmessageTest::testSerialize2()
{
    QByteArray a;
    QByteArray b;
    QDataStream sa(&a, QIODevice::WriteOnly);
    QDataStream sb(&b, QIODevice::WriteOnly);

    sa << "tx";

    sb << "register";
    sb << "ff2aa";
    sb << (quint32)55.789;
    sb << QByteArray("owner");
    sb << "name";

    sa << b;

    QDataStream ra(&a, QIODevice::ReadOnly);

    Message m;
    ra >> m;

    m.debug();
}

QTEST_APPLESS_MAIN(TestmessageTest)

#include "tst_testmessagetest.moc"
