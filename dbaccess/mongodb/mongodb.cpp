#include "mongodb.h"
#include <QDebug>

#include "headermongodb.h"
#include "registertransactionmongodb.h"

MongoDB::MongoDB()
{
    mongoc_init();
    QString str = URL+HOST+":"+PORT;
    client = mongoc_client_new(str.toStdString().c_str());
    database = mongoc_client_get_database(client, DB_NAME.toStdString().c_str());
    blocks = mongoc_client_get_collection(client, DB_NAME.toStdString().c_str(), "blocks");
}

void MongoDB::saveHeader(Header header)
{
    bson_error_t error;
    HeaderMongoDB headerMongoDb;
    bson_t* doc = headerMongoDb.getDoc(header);
    mongoc_collection_insert_one(blocks, doc, NULL, NULL, &error);
}

void MongoDB::saveTransaction(ATransaction *tx)
{
    bson_error_t error;
    bson_t* doc;

    if (strcmp(tx->getType(), "REG") == 0) {
        RegisterTransactionMongoDB txMongo;
        doc = txMongo.getDoc(dynamic_cast<RegisterTransaction*>(tx));
    }

    mongoc_collection_insert_one(blocks, doc, NULL, NULL, &error);
}

void MongoDB::saveBlock(Block block)
{
    HeaderMongoDB headerMongoDb;
    bson_t* headerDoc = headerMongoDb.getDoc(block.getHeader());
    bson_t child;

    BSON_APPEND_ARRAY_BEGIN(headerDoc, "tx", &child);
    QVector<ATransaction*> tx = block.getTransactions();
    for (int i = 0; i < tx.size(); i++) {
        bson_t *txDoc;
        ATransaction *txa = tx.at(i);
        if (strcmp(txa->getType(), "REG") == 0) {
            RegisterTransactionMongoDB txMongo;
            txDoc = txMongo.getDoc(dynamic_cast<RegisterTransaction*>(txa));
            bson_append_document(&child, "xx", -1, txDoc);
        }
    }
    bson_append_array_end(headerDoc, &child);

    bson_error_t error;
    mongoc_collection_insert_one(blocks, headerDoc, NULL, NULL, &error);
}

void MongoDB::resetBlocks()
{
    bson_t *command;
    bson_t reply;
    bson_error_t error;

    command = BCON_NEW("drop", BCON_UTF8("blocks"));
    mongoc_collection_command_simple(blocks, command, NULL, &reply, &error);

    bson_destroy(command);
    bson_destroy(&reply);
}
