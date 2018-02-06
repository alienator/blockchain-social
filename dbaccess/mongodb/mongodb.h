#ifndef NODEMONGODB_H
#define NODEMONGODB_H

#include "mongoc.h"

#include <QString>
#include "../iadapter.h"
#include "../core/block/header.h"
#include "../core/block/transaction/atransaction.h"
#include "../core/block/block.h"

class MongoDB : public IAdapter
{
private:
    const QString URL = "mongodb://";
    const QString HOST = "localhost";
    const QString PORT = "27017";
    const QString DB_NAME = "nodeclient_qt";

    mongoc_client_t* client;
    mongoc_database_t* database;
    mongoc_collection_t* blocks;

public:
    MongoDB();
    void saveHeader(Header header);
    void saveTransaction(ATransaction *tx);
    void saveBlock(Block block);
    void resetBlocks();
    bool hasTransaction(QByteArray hash);
    Header getLastHeader();
    quint32 getHeight();
};

#endif // NODEMONGODB_H

