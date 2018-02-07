#include "txoutput.h"

TxOutput::TxOutput(QByteArray address, double value)
{
    this->addres = address;
    this->value = value;
}

QByteArray TxOutput::serialize()
{
    QByteArray bytes;
    bytes.append(addres);
    bytes.append(QByteArray::number(value));

    return bytes;
}

QByteArray TxOutput::getAddress()
{
    return addres;
}

double TxOutput::getValue()
{
    return value;
}
