#include "genesis.h"
#include "transaction/registertransaction.h"

#include <QDateTime>
#include <QDate>
#include <QDebug>

Genesis::Genesis()
{
    RegisterTransaction* tx = new RegisterTransaction(QByteArray("x"), 100000000, "new_coin");
    addTransaction(tx);

    Header header;
    header.setIndex(0);
    header.setPreviousHash(QByteArray("00000000000"));
    QDateTime timestamp = QDateTime(QDate(2018, 1, 1), QTime(1, 1, 1));
    header.setTimestamp(timestamp.toUTC().toMSecsSinceEpoch());
    header.setMerkleRoot(generateMerkleRoot());
    header.setHash(header.calculateHash());
    addHeader(header);
}
