#ifndef ASIGNABLE_H
#define ASIGNABLE_H

#include <QByteArray>

class ASignable
{
protected:
    QByteArray hash;
public:
    virtual QByteArray getHash(){ return hash; }
    virtual QByteArray calculateHash() = 0;
};

#endif // ASIGNABLE_H
