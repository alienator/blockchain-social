#include "mongodb.h"
#include <QDebug>

#include "headermongodb.h"
#include "registertransactionmongodb.h"
#include "transferecetransactionmongodb.h"

MongoDB::MongoDB()
{
    mongoc_init();
    QString str = URL+HOST+":"+PORT;
    client = mongoc_client_new(str.toStdString().c_str());
    database = mongoc_client_get_database(client, DB_NAME.toStdString().c_str());
    blocks = mongoc_client_get_collection(client, DB_NAME.toStdString().c_str(), "blocks");

    //try to connect to mongodb
    bson_error_t error;
    bson_t *command, reply;
    command = BCON_NEW ("ping", BCON_INT32 (1));
    connected = mongoc_client_command_simple(client, "admin", command, NULL, &reply, &error);

    if (!connected) {
        /*fprintf (stderr, "%s\n", error.message);
        return EXIT_FAILURE;*/
        qDebug() << error.message;
    }
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
        else if (strcmp(txa->getType(), "TRA") == 0) {
            TransfereceTransactionMongoDb txMongo;
            txDoc = txMongo.getDoc(dynamic_cast<TransferenceTransaction*>(txa));
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

bool MongoDB::hasTransaction(QByteArray hash)
{
    bson_error_t error;
    int64_t count;
    bson_t *query;

    query = bson_new();
    BSON_APPEND_UTF8 (query, "tx.txhash", hash.toHex());

    count = mongoc_collection_count(
                blocks, MONGOC_QUERY_NONE, query, 0, 0,
                NULL, &error
                );

    if (count == 1) {
        return true;
    } else {
        return false;
    }
}

Header MongoDB::getLastHeader()
{
    bson_t *query;
    bson_t *opts;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_iter_t iter;

    query = bson_new();
    opts = BCON_NEW(
                    "limit", BCON_INT64 (1),
                    "sort", "{", "index", BCON_INT32 (-1), "}",
                    "projection", "{", "tx", BCON_BOOL(false), "}"
                    );

    cursor = mongoc_collection_find_with_opts(blocks, query, opts, NULL);
    mongoc_cursor_next(cursor, &doc);

    Header header;
    if (bson_iter_init(&iter, doc)) {
       while (bson_iter_next(&iter)) {
           const char *key = bson_iter_key(&iter);
           const bson_value_t *value = bson_iter_value(&iter);

           if (strcmp(key, "hash") == 0) {
               QString str = QString::fromUtf8(value->value.v_utf8.str);
               header.setHash(QByteArray::fromHex(str.toLatin1()));
           }

           else if (strcmp(key, "index") == 0) {
                header.setIndex(value->value.v_int32);
           }

           else if (strcmp(key, "timestamp") == 0) {
                header.setTimestamp(value->value.v_int64);
           }

           else if (strcmp(key, "previous_hash") == 0) {
               QString str = QString::fromUtf8(value->value.v_utf8.str);
               header.setPreviousHash(QByteArray::fromHex(str.toLatin1()));
           }

           else if (strcmp(key, "merkle_root") == 0) {
               QString str = QString::fromUtf8(value->value.v_utf8.str);
                header.setMerkleRoot(QByteArray::fromHex(str.toLatin1()));
           }

       }
    }

    return header;
}

quint32 MongoDB::getHeight()
{
    bson_error_t error;
    int64_t count;
    bson_t *query;

    query = bson_new();
    //BSON_APPEND_UTF8 (query, "tx.txhash", hash.toHex());

    count = mongoc_collection_count(
                blocks, MONGOC_QUERY_NONE, query, 0, 0,
                NULL, &error
                );

    return count;
}

bool MongoDB::isConnected()
{
    return connected;
}

QList<Block> MongoDB::outputs(QString address)
{
    bson_t *query;
    bson_t *opts;
    mongoc_cursor_t *cursor;
    const bson_t *doc;

    query = bson_new();
    BSON_APPEND_UTF8(query, "tx.outputs.address", address.toStdString().c_str());
    opts = BCON_NEW(
                    "sort", "{", "index", BCON_INT32 (-1), "}"
                    );

    cursor = mongoc_collection_find_with_opts(blocks, query, opts, NULL);

    QList<Block> bs;
    while(mongoc_cursor_next(cursor, &doc)){
        //header block
        HeaderMongoDB hmongo;
        Header header;
        Block block;
        header = hmongo.getHeader(doc);
        block.addHeader(header);

        //tx
        bson_iter_t iter;
        bson_iter_init(&iter, doc);
        bson_iter_find(&iter, "tx");
        const uint8_t *data = NULL;
        uint32_t len = 0;
        bson_iter_array(&iter, &len, &data);
        bson_t *sub = bson_new_from_data(data, len);
        bson_iter_t it;
        bson_iter_init(&it, sub);

        TransfereceTransactionMongoDb txmongo;
        while (bson_iter_next(&it)) {
            const uint8_t *dat = NULL;
            uint32_t le = 0;
            bson_iter_document(&it, &le, &dat);
            bson_t *ssub = bson_new_from_data(dat, le);

            block.addTransaction(txmongo.getTx(ssub));
        }

        bs.append(block);
        block.debug();
    }

    return bs;
}
