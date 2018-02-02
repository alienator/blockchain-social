#ifndef NODE_H
#define NODE_H

#include "node_global.h"
#include "server.h"

class NODESHARED_EXPORT Node
{

private:
    Server server;

public:
    Node();
};

#endif // NODE_H
