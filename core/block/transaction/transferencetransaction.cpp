#include "transferencetransaction.h"
#include <QCryptographicHash>
#include <QDebug>

TransferenceTransaction::TransferenceTransaction()
{
    strcpy(this->type, "TRA");
}

QByteArray TransferenceTransaction::getSource()
{
    return source;
}

QByteArray TransferenceTransaction::getTarget()
{
    return target;
}

double TransferenceTransaction::getAmount()
{
    return amount;
}

QByteArray TransferenceTransaction::calculateHash()
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(this->type);

    QByteArray inputsBytes;
    for (int i = 0; i < inputs.size(); i++) {
        inputsBytes.append(inputs[i]->serialize());
    }

    hash.addData(inputsBytes);

    QByteArray outputsBytes;
    for (int i = 0; i < outputs.size(); i++) {
        outputsBytes.append(outputs[i]->serialize());
    }

    hash.addData(outputsBytes);

    return hash.result();
}

void TransferenceTransaction::debug()
{
    qDebug() << "TransferenceTransaction["
             << "hash=" << this->hash.toHex()
             << ", type=" << this->type
             << ", inputs:" << this->inputs
             << ", outputs:" << this->outputs
             << "]";
}

quint32 TransferenceTransaction::getSize()
{
    quint32 size = 0;
    size += 3; //type
    size += source.size();
    size += target.size();

    for (int i = 0; i < inputs.size(); i++) {
        size += inputs[i]->serialize().size();
    }

    for (int i = 0; i < outputs.size(); i++) {
        size += outputs[i]->serialize().size();
    }

    size += 8;

    return size;
}

QList<TxOutput *> TransferenceTransaction::getOutputs()
{
    return outputs;
}

QList<TxInput *> TransferenceTransaction::getInputs()
{
    return inputs;
}

void TransferenceTransaction::addInput(TxInput *in)
{
    inputs.append(in);
}

void TransferenceTransaction::addOutput(TxOutput *out)
{
    outputs.append(out);
}

void TransferenceTransaction::setHash(QByteArray hash)
{
    this->hash = hash;
}
