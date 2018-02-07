#ifndef HEADERMONGODB_H
#define HEADERMONGODB_H

#include "../core/block/header.h"
#include <mongoc.h>

class HeaderMongoDB
{
public:
    HeaderMongoDB();
    bson_t *getDoc(Header header);

    Header getHeader(const bson_t *doc);
};

#endif // HEADERMONGODB_H
