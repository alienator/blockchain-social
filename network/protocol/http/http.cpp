#include "http.h"

#include <QDebug>

Http::Http()
{
}

bool Http::connect()
{
    QNetworkAccessManager *am = new QNetworkAccessManager();
    //am->connectToHost();
    QNetworkReply *r = am->get(QNetworkRequest(QUrl("http://google.com")));
    qDebug() << r->readAll();
    return true;
}
