#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "header.h"
#include "../dbaccess/dbaccess.h"

class BlockChain
{
private:
    Dbaccess *dbaccess;
    static BlockChain* instance;
    BlockChain();
public:
    static BlockChain* getInstance();
    void createGenesis();
    Header getLastHeader();
    //void saveBlock(Block block);
};

#endif // BLOCKCHAIN_H
