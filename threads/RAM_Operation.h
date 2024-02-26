#ifndef RAM_OPERATION_H
#define RAM_OPERATION_H

#include "State.h"

class RAM_Operation : public State
{
public:
    RAM_Operation();
    virtual ~RAM_Operation();

    void run() override;
};

#endif
