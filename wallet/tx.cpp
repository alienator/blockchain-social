#include "tx.h"

Tx::Tx()
{

}

void Tx::setHash(QString hash)
{
    this->hash = hash;
}

void Tx::setState(quint32 state)
{
    this->state = state;
}

void Tx::setValue(double value)
{
    this->value = value;
}

QString Tx::getHash()
{
    return hash;
}

double Tx::getValue()
{
    return value;
}

quint32 Tx::getState()
{
    return state;
}
