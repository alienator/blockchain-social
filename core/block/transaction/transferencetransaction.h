#ifndef TRANSFERENCETRANSACTION_H
#define TRANSFERENCETRANSACTION_H

#include <QList>

#include "atransaction.h"
#include "txoutput.h"
#include "txinput.h"

class TransferenceTransaction : public ATransaction
{
protected:
    QByteArray source;
    QByteArray target;
    double amount;

    QList<TxInput *> inputs;
    QList<TxOutput *> outputs;

public:
    TransferenceTransaction();
    QByteArray getSource();
    QByteArray getTarget();
    double getAmount();
    QByteArray calculateHash();
    quint32 getSize();
    void debug();

    void addInput(TxInput *in);
    void addOutput(TxOutput *out);

    QList<TxInput *> getInputs();
    QList<TxOutput *> getOutputs();

    void setHash(QByteArray hash);
};

#endif // TRANSFERENCETRANSACTION_H
