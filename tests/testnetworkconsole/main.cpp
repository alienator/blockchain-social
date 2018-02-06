#include <QCoreApplication>
#include "../../network/node/node.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Node n;

    return a.exec();
}
