#ifndef ATRANSACTION_H
#define ATRANSACTION_H

#include "../../asignable.h"
#include "../../iverifiable.h"

class ATransaction: public ASignable, public IVerifiable {
protected:
    /**
     * Type of transaction 3 chars
     * miner MIN
     * contract CTR
     * transfer TRA
     * register REG
     * etc
     * @brief type
     */
    char type[3];
public:
    char* getType() {
        return type;
    }

    virtual void debug() = 0;
};

#endif // ATRANSACTION_H
