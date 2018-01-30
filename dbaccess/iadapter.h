#ifndef IADAPTER_H
#define IADAPTER_H

#include "../core/block/block.h"

class IAdapter
{
public:
    virtual void saveBlock(Block block) = 0;
    virtual void resetBlocks() = 0;
};

#endif // IADAPTER_H
