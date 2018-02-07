#include "tx.h"

Tx::Tx(QString target, double amount)
{
    this->target = target;
    this->amount = amount;
}

TransferenceTransaction Tx::buildTx()
{
    //TransferenceTransaction tx;

}
