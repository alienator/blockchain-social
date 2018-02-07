#ifndef TXOUTPUT_H
#define TXOUTPUT_H

#include <QByteArray>

class TxOutput
{
private:
    QByteArray addres;
    double value;

public:
    TxOutput(QByteArray address, double value);
    QByteArray serialize();
    QByteArray getAddress();
    double getValue();

};

#endif // TXOUTPUT_H
