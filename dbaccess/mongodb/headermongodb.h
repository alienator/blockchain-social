#ifndef HEADERMONGODB_H
#define HEADERMONGODB_H

#include "../core/block/header.h"
#include <mongoc.h>

class HeaderMongoDB
{
public:
    HeaderMongoDB();
    bson_t *getDoc(Header header);
};

#endif // HEADERMONGODB_H
