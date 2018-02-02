#ifndef APAYLOAD_H
#define APAYLOAD_H

#include <QByteArray>

#include "../../core/block/block.h"
#include "../../core/block/transaction/atransaction.h"

class APayload
{
public:
    virtual QByteArray serializeTx(ATransaction *tx) = 0;
    virtual QByteArray serializeBlock(Block block) = 0;
    virtual ATransaction *unserializeTx(QByteArray buffer) = 0;
    virtual Block unserializeBlock(QByteArray buffer) = 0;
}
#endif // APAYLOAD_H
