#include "registertransactionmongodb.h"

RegisterTransactionMongoDB::RegisterTransactionMongoDB()
{

}

bson_t* RegisterTransactionMongoDB::getDoc(RegisterTransaction* tx)
{
    bson_oid_t oid;
    bson_t* doc = bson_new();
    bson_oid_init(&oid, NULL);
    BSON_APPEND_OID(doc, "_id", &oid);
    BSON_APPEND_UTF8(doc, "txhash", tx->getHash().toHex().toStdString().c_str());
    BSON_APPEND_INT32(doc, "size", tx->getSize());
    BSON_APPEND_UTF8(doc, "type", tx->getType());
    BSON_APPEND_UTF8(doc, "name", tx->getName().toStdString().c_str());
    BSON_APPEND_DOUBLE(doc, "amount", tx->getAmount());
    BSON_APPEND_UTF8(doc, "owner", tx->getOwner().toHex().toStdString().c_str());

    return doc;
}
