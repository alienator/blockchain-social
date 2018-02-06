#include "dbaccess.h"

#include "mongodb/mongodb.h"

Dbaccess *Dbaccess::instance = NULL;

Dbaccess::Dbaccess()
{
    adapter = new MongoDB;
}

Dbaccess *Dbaccess::getInstance()
{
    if (!instance) {
        instance = new Dbaccess;
    }

    return instance;
}

IAdapter *Dbaccess::getAdapter()
{
    return Dbaccess::adapter;
}

void Dbaccess::saveBlock(Block block)
{
    adapter->saveBlock(block);
}

bool Dbaccess::hasTransaction(QByteArray hash)
{
    return adapter->hasTransaction(hash);
}

Header Dbaccess::getLastHeader()
{
    return adapter->getLastHeader();
}
quint32 Dbaccess::getHeight()
{
    return adapter->getHeight();
}
