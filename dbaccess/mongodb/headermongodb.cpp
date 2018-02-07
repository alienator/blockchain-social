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

Header HeaderMongoDB::getHeader(const bson_t *doc)
{
    //const bson_t *doc;
    bson_iter_t iter;

    Header header;
    if (bson_iter_init(&iter, doc)) {
       while (bson_iter_next(&iter)) {
           const char *key = bson_iter_key(&iter);
           const bson_value_t *value = bson_iter_value(&iter);

           if (strcmp(key, "hash") == 0) {
               header.setHash(QByteArray::fromHex(QString::fromUtf8(value->value.v_utf8.str).toLatin1()));
           }
           else if (strcmp(key, "index") == 0) {
               header.setIndex(value->value.v_int32);
           }
           else if (strcmp(key, "timestamp") == 0) {
               header.setTimestamp(value->value.v_int64);
           }
           else if (strcmp(key, "previous_hash") == 0) {
               header.setPreviousHash(QByteArray::fromHex(QString::fromUtf8(value->value.v_utf8.str).toLatin1()));
           }
           else if (strcmp(key, "merkle_root") == 0) {
               header.setMerkleRoot(QByteArray::fromHex(QString::fromUtf8(value->value.v_utf8.str).toLatin1()));
           } else {
               continue;
           }
       }
    }

    return header;
}
