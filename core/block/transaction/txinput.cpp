#include "txinput.h"

TxInput::TxInput(QByteArray ph, quint32 pi)
{
    previous_hash = ph;
    previous_index = pi;
}

QByteArray TxInput::serialize()
{
    QByteArray bytes;
    bytes.append(previous_hash);
    bytes.append(previous_index);

    return bytes;
}

QByteArray TxInput::getPreviousHash()
{
    return previous_hash;
}

quint32 TxInput::getPreviousIndex()
{
    return previous_index;
}
