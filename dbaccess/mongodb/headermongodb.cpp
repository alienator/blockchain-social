#include "headermongodb.h"

HeaderMongoDB::HeaderMongoDB()
{

}

bson_t* HeaderMongoDB::getDoc(Header header)
{
    bson_oid_t oid;
    bson_t* doc = bson_new();
    bson_oid_init(&oid, NULL);
    BSON_APPEND_OID(doc, "_id", &oid);
    BSON_APPEND_UTF8(doc, "hash", header.getHash().toHex().toStdString().c_str());
    BSON_APPEND_INT32(doc, "size", header.getSize());
    BSON_APPEND_INT32(doc, "index", header.getIndex());
    BSON_APPEND_INT64(doc, "timestamp", header.getTimestamp());
    BSON_APPEND_UTF8(doc, "previous_hash", header.getPreviousHash().toHex().toStdString().c_str());
    BSON_APPEND_UTF8(doc, "merkle_root", header.getMerkleRoot().toHex().toStdString().c_str());

    return doc;
}
