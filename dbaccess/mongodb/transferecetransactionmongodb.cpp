#include "transferecetransactionmongodb.h"
#include <QDebug>

TransfereceTransactionMongoDb::TransfereceTransactionMongoDb()
{

}

bson_t *TransfereceTransactionMongoDb::getDoc(TransferenceTransaction *tx)
{
    bson_oid_t oid;
    bson_t* doc = bson_new();
    bson_oid_init(&oid, NULL);
    BSON_APPEND_OID(doc, "_id", &oid);
    BSON_APPEND_UTF8(doc, "txhash", tx->getHash().toHex().toStdString().c_str());
    BSON_APPEND_INT32(doc, "size", tx->getSize());
    BSON_APPEND_UTF8(doc, "type", tx->getType());

    //array inputs doc
    bson_t child;
    BSON_APPEND_ARRAY_BEGIN(doc, "inputs", &child);
    QList<TxInput *> inputs = tx->getInputs();
    for (int i = 0; i < inputs.size(); i++) {
        bson_t *txDoc;
        TxInput *input = inputs.at(i);
        txDoc = getInputsDoc(input);
        bson_append_document(&child, "in", -1, txDoc);
    }
    bson_append_array_end(doc, &child);

    //array outputs doc
    bson_t child2;
    BSON_APPEND_ARRAY_BEGIN(doc, "outputs", &child2);
    QList<TxOutput *> outputs = tx->getOutputs();
    for (int i = 0; i < outputs.size(); i++) {
        bson_t *txDoc;
        TxOutput *ouput = outputs.at(i);
        txDoc = getOutputsDoc(ouput);
        bson_append_document(&child2, "out", -1, txDoc);
    }
    bson_append_array_end(doc, &child2);

    return doc;
}

bson_t *TransfereceTransactionMongoDb::getInputsDoc(TxInput *in)
{
    bson_oid_t oid;
    bson_t* doc = bson_new();
    bson_oid_init(&oid, NULL);
    BSON_APPEND_OID(doc, "_id", &oid);
    BSON_APPEND_UTF8(doc, "previous_hash", in->getPreviousHash().toHex().toStdString().c_str());
    BSON_APPEND_INT32(doc, "previous_index", in->getPreviousIndex());

    return doc;
}

bson_t *TransfereceTransactionMongoDb::getOutputsDoc(TxOutput *out)
{
    bson_oid_t oid;
    bson_t* doc = bson_new();
    bson_oid_init(&oid, NULL);
    BSON_APPEND_OID(doc, "_id", &oid);
    BSON_APPEND_UTF8(doc, "address", out->getAddress().toHex().toStdString().c_str());
    BSON_APPEND_DOUBLE(doc, "value", out->getValue());

    return doc;
}

TxOutput *TransfereceTransactionMongoDb::getOutput(bson_t *doc)
{
    bson_iter_t iter;
    QByteArray address;
    double value;

    if (bson_iter_init(&iter, doc)) {
       while (bson_iter_next(&iter)) {
           const char *key = bson_iter_key(&iter);
           const bson_value_t *vo = bson_iter_value(&iter);

           if (strcmp(key, "address") == 0) {
               address.append(QByteArray::fromHex(QString::fromUtf8(vo->value.v_utf8.str).toLatin1()));
           }
           else if (strcmp(key, "value") == 0) {
               value = vo->value.v_double;
           }
       }
    }

    return new TxOutput(address, value);
}

TxInput *TransfereceTransactionMongoDb::getInput(bson_t *doc)
{

    bson_iter_t iter;
    QByteArray previous_hash;
    quint32 previous_index;

    if (bson_iter_init(&iter, doc)) {
       while (bson_iter_next(&iter)) {
           const char *key = bson_iter_key(&iter);
           const bson_value_t *vo = bson_iter_value(&iter);

           if (strcmp(key, "previous_hash") == 0) {
               previous_hash.append(QByteArray::fromHex(QString::fromUtf8(vo->value.v_utf8.str).toLatin1()));
           }
           else if (strcmp(key, "previous_index") == 0) {
               previous_index = vo->value.v_int32;
           }
       }
    }

    return new TxInput(previous_hash, previous_index);
}

TransferenceTransaction *TransfereceTransactionMongoDb::getTx(bson_t *doc)
{
    bson_iter_t iter;
    TransferenceTransaction *tx = new TransferenceTransaction();

    if (bson_iter_init(&iter, doc)) {
       while (bson_iter_next(&iter)) {
           const char *key = bson_iter_key(&iter);
           const bson_value_t *vo = bson_iter_value(&iter);

           if (strcmp(key, "txhash") == 0) {
               tx->setHash(QByteArray::fromHex(QString::fromUtf8(vo->value.v_utf8.str).toLatin1()));
           }
           else if (strcmp(key, "inputs") == 0 && vo->value_type == BSON_TYPE_ARRAY) {
               const uint8_t *data = NULL;
               uint32_t len = 0;
               bson_iter_array(&iter, &len, &data);
               bson_t *sub = bson_new_from_data(data, len);
               bson_iter_t it;
               bson_iter_init(&it, sub);

               //QList<TxInput *> inputs;
               while(bson_iter_next(&it)) {
                   const char *k = bson_iter_key(&it);
                   const bson_value_t *v = bson_iter_value(&it);

                   if (v->value_type == BSON_TYPE_DOCUMENT) {
                       const uint8_t *dat = NULL;
                       uint32_t le = 0;
                       bson_iter_document(&it, &le, &dat);
                       bson_t *ssub = bson_new_from_data(dat, le);

                       tx->addInput(getInput(ssub));
                   }
               }
           }
           else if (strcmp(key, "outputs") == 0 && vo->value_type == BSON_TYPE_ARRAY) {
               const uint8_t *data = NULL;
               uint32_t len = 0;
               bson_iter_array(&iter, &len, &data);
               bson_t *sub = bson_new_from_data(data, len);
               bson_iter_t it;
               bson_iter_init(&it, sub);

               //QList<TxOutput *> outputs;
               while(bson_iter_next(&it)) {
                   const char *k = bson_iter_key(&it);
                   const bson_value_t *v = bson_iter_value(&it);

                   if (v->value_type == BSON_TYPE_DOCUMENT) {
                       const uint8_t *dat = NULL;
                       uint32_t le = 0;
                       bson_iter_document(&it, &le, &dat);
                       bson_t *ssub = bson_new_from_data(dat, le);

                       tx->addOutput(getOutput(ssub));
                   }
               }
           }
       }
    }

    return tx;
}
