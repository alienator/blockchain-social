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
    Dbaccess::getInstance()->saveBlock(genesis);
}

bool BlockChain::hasTransaction(QByteArray hash)
{
    return Dbaccess::getInstance()->hasTransaction(hash);
}

Header BlockChain::getLastHeader()
{
    return Dbaccess::getInstance()->getLastHeader();
}

void BlockChain::saveBlock(Block block)
{
    Dbaccess::getInstance()->saveBlock(block);
}

quint32 BlockChain::getHeight()
{
    return Dbaccess::getInstance()->getHeight();
}

QList<Block> BlockChain::outputs(QString address)
{
    return Dbaccess::getInstance()->outputs(address);
}
