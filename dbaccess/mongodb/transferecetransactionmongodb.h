#ifndef TRANSFERECETRANSACTIONMONGODB_H
#define TRANSFERECETRANSACTIONMONGODB_H

#include "../../core/block/transaction/transferencetransaction.h"
#include <mongoc.h>

class TransfereceTransactionMongoDb
{
public:
    TransfereceTransactionMongoDb();
    bson_t* getDoc(TransferenceTransaction *tx);
    bson_t* getInputsDoc(TxInput *in);
    bson_t* getOutputsDoc(TxOutput *out);

    TxOutput *getOutput(bson_t *doc);
    TxInput *getInput(bson_t *doc);
    TransferenceTransaction *getTx(bson_t *doc);
};

#endif // TRANSFERECETRANSACTIONMONGODB_H
