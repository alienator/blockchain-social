#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "header.h"
#include "block.h"
#include "header.h"
#include "../../dbaccess/dbaccess.h"

class BlockChain
{
private:
    static BlockChain* instance;
    BlockChain();
public:
    static BlockChain* getInstance();
    void createGenesis();
    bool hasTransaction(QByteArray hash);
    Header getLastHeader();
    void saveBlock(Block block);
    quint32 getHeight();
    QList<Block> outputs(QString address);
};

#endif // BLOCKCHAIN_H
