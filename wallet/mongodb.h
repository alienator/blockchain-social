#ifndef MONGODB_H
#define MONGODB_H

#include <QDebug>
#include "mongoc.h"
#include "tx.h"

namespace ThisWallet {

class MongoDb
{
private:
    const QString URL = "mongodb://";
    const QString HOST = "localhost";
    const QString PORT = "27017";
    const QString DB_NAME = "wallet_qt";

    mongoc_client_t* client;
    mongoc_database_t* database;
    mongoc_collection_t* transactions;

    bool connected;

public:
    MongoDb();
    bool isConnected();
    void saveTransaction(QString hash, double value, int state);
    QList<Tx> loadCredits();
    void updateState(QString hash, quint32 state);
};

}
#endif // MONGODB_H
