#include "mongodb.h"
using namespace ThisWallet;

MongoDb::MongoDb()
{
    qDebug() << "init....";
    mongoc_init();
    QString str = URL+HOST+":"+PORT;
    client = mongoc_client_new(str.toStdString().c_str());
    database = mongoc_client_get_database(client, DB_NAME.toStdString().c_str());
    transactions = mongoc_client_get_collection(client, DB_NAME.toStdString().c_str(), "transactions");

    //try to connect to mongodb
    bson_error_t error;
    bson_t *command, reply;
    command = BCON_NEW ("ping", BCON_INT32 (1));
    connected = mongoc_client_command_simple(client, "admin", command, NULL, &reply, &error);

    if (!connected) {
        qDebug() << error.message;
    }
    else {
        qDebug() << "conectado!";
    }
}

bool MongoDb::isConnected()
{
    return connected;
}

void MongoDb::saveTransaction(QString hash, double value, int state)
{
    bson_oid_t oid;
    bson_oid_init(&oid, NULL);

    bson_t *doc = bson_new();
    BSON_APPEND_OID(doc, "_id", &oid);
    BSON_APPEND_UTF8(doc, "hash", hash.toStdString().c_str());
    BSON_APPEND_DOUBLE(doc, "value", value);
    BSON_APPEND_INT32(doc, "state", state);

    bson_error_t error;
    mongoc_collection_insert_one(transactions, doc, NULL, NULL, &error);
    qDebug() << error.message;
}

QList<Tx> MongoDb::loadCredits()
{
    bson_t child;
    bson_t *query;
    bson_t *opts;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_iter_t iter;

    query = bson_new();
    BSON_APPEND_DOCUMENT_BEGIN (query, "state", &child);
    //BSON_APPEND_INT32(&child, "$ne", 4);
    BSON_APPEND_INT32(&child, "$ne", 3);
    bson_append_document_end (query, &child);

    opts = BCON_NEW(
                    "sort", "{", "_id", BCON_INT32 (-1), "}"
                    );

    cursor = mongoc_collection_find_with_opts(transactions, query, opts, NULL);

    QList<Tx> txs;
    while(mongoc_cursor_next(cursor, &doc)) {
        if (bson_iter_init(&iter, doc)) {
           Tx tx;

           while (bson_iter_next(&iter)) {
               const char *key = bson_iter_key(&iter);
               const bson_value_t *value = bson_iter_value(&iter);


               if (strcmp(key, "hash") == 0) {
                    tx.setHash(QString::fromUtf8(value->value.v_utf8.str));
               }
               else if (strcmp(key, "value") == 0) {
                   tx.setValue(value->value.v_double);
               }
               else if(strcmp(key, "state") == 0) {
                   tx.setState(value->value.v_int32);
               }
            }

            txs.append(tx);
        }
    }

    return txs;
}

void MongoDb::updateState(QString hash, quint32 state)
{
    bson_t *update = NULL;
    bson_t *query = NULL;
    bson_error_t error;

    query = BCON_NEW ("hash", hash.toStdString().c_str());
    update = BCON_NEW ("$set",
                          "{",
                          "state",
                          BCON_INT32 (state),
                          "updated",
                          BCON_BOOL (true),
                          "}");

    if (!mongoc_collection_update_one (transactions, query, update, NULL, NULL, &error)) {
        qDebug() << error.message;
    }

    mongoc_collection_destroy(transactions);
    mongoc_client_destroy(client);
    mongoc_cleanup();
}
