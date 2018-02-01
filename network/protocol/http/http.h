#ifndef HTTP_H
#define HTTP_H

#include "http_global.h"

#include <QtNetwork>
#include <QUrl>

class HTTPSHARED_EXPORT Http
{

public:
    Http();
    bool connect();
};

#endif // HTTP_H
