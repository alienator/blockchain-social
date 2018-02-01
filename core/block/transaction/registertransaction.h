#ifndef REGISTERTRANSACTION_H
#define REGISTERTRANSACTION_H
#include <QString>

#include "atransaction.h"

class RegisterTransaction : public ATransaction
{
protected:
    double amount;
    QString name;
    QByteArray owner;
public:
    RegisterTransaction(QByteArray owner, double amount, QString name);
    QByteArray getOwner();
    double getAmount();
    QString getName();
    quint32 getSize();
    QByteArray calculateHash();
    void debug();
    virtual ~RegisterTransaction() {}
};

#endif // REGISTERTRANSACTION_H
