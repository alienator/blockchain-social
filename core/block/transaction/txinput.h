#ifndef TXINPUT_H
#define TXINPUT_H

#include <QByteArray>

class TxInput
{
private:
    QByteArray previous_hash;
    quint32 previous_index;

public:
    TxInput(QByteArray ph, quint32 pi);
    QByteArray serialize();
    QByteArray getPreviousHash();
    quint32 getPreviousIndex();
};

#endif // TXINPUT_H
