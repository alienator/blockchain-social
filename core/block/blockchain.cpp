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

/*Header BlockChain::getLastHeader()
{
    //todo: adapter last header
    //return NULL;
}*/
