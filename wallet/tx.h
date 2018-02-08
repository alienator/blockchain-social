#ifndef TX_H
#define TX_H

#include "../core/block/transaction/transferencetransaction.h"
#include <QString>

class Tx
{
private:
    QString hash;
    double value;
    quint32 state;

public:
    Tx();
    void setHash(QString hash);
    void setValue(double value);
    void setState(quint32 state);

    QString getHash();
    double getValue();
    quint32 getState();
};

#endif // TX_H
