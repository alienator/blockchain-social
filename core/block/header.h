#ifndef HEADER_H
#define HEADER_H

#include <QByteArray>
#include <QString>
#include <QDebug>

#include "../asignable.h"
#include "../iverifiable.h"


class Header : public ASignable, public IVerifiable
{
private:
    quint32 index;
    QByteArray previous_hash;
    QByteArray merkle_root;
    qint64 timestamp;
public:
    QByteArray calculateHash();
    quint32 getSize();
    bool verify();
    void setHash(QByteArray hash);
    quint32 getIndex();
    void setIndex(quint32 index);
    void setPreviousHash(QByteArray previous_hash);
    QByteArray getPreviousHash();
    void setMerkleRoot(QByteArray merkle_root);
    QByteArray getMerkleRoot();
    void setTimestamp(qint64 timestamp);
    qint64 getTimestamp();
    void regenerate();
    void debug();
private:
    void genTimestamp();
};

#endif // HEADER_H
