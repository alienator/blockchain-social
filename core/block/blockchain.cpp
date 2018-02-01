#include "blockchain.h"

#include <QDateTime>
#include <QDate>
#include <QTime>

#include "header.h"
#include "transaction/registertransaction.h"
#include "genesis.h"

BlockChain* BlockChain::instance = NULL;

BlockChain::BlockChain()
{
    dbaccess = Dbaccess::getInstance();
}

BlockChain* BlockChain::getInstance()
{
    if (!instance) {
        instance = new BlockChain;
    }

    return instance;
}

void BlockChain::createGenesis()
{
    Genesis genesis;
    dbaccess->saveBlock(genesis);
}

bool BlockChain::hasTransaction(QByteArray hash)
{
    return dbaccess->hasTransaction(hash);
}

Header BlockChain::getLastHeader()
{
    return dbaccess->getLastHeader();
}

void BlockChain::saveBlock(Block block)
{
    dbaccess->saveBlock(block);
}
