#ifndef IADAPTER_H
#define IADAPTER_H

#include "../core/block/block.h"
#include <QByteArray>

class IAdapter
{
public:
    virtual void saveBlock(Block block) = 0;
    virtual void resetBlocks() = 0;
    virtual bool hasTransaction(QByteArray hash) = 0;
    virtual Header getLastHeader() = 0;
    virtual quint32 getHeight() = 0;
};

#endif // IADAPTER_H
