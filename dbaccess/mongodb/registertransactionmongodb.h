#ifndef REGISTERTRANSACTIONMONGODB_H
#define REGISTERTRANSACTIONMONGODB_H

#include "../core/block/transaction/registertransaction.h"
#include <mongoc.h>

class RegisterTransactionMongoDB
{
public:
    RegisterTransactionMongoDB();
    bson_t* getDoc(RegisterTransaction* tx);
};

#endif // REGISTERTRANSACTIONMONGODB_H
