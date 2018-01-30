#ifndef DBACCESS_H
#define DBACCESS_H

#include "dbaccess_global.h"
#include "iadapter.h"
#include "../core/block/block.h"

class DBACCESSSHARED_EXPORT Dbaccess
{
private:
    IAdapter *adapter;
    static Dbaccess *instance;
    Dbaccess();

public:
    static Dbaccess *getInstance();
    IAdapter *getAdapter();
    void saveBlock(Block block);
};

#endif // DBACCESS_H
