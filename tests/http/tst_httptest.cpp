#include <QString>
#include <QtTest>

#include "../../network/protocol/http/http.h"

class HttpTest : public QObject
{
    Q_OBJECT

public:
    HttpTest();

private Q_SLOTS:
    void testConection();
};

HttpTest::HttpTest()
{
}

void HttpTest::testConection()
{
    Http http;
    ///http.connect();

    QVERIFY(http.connect());
}

QTEST_APPLESS_MAIN(HttpTest)

#include "tst_httptest.moc"
