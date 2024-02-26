// BLE_Stack_Operation.h
#ifndef BLE_STACK_OPERATION_H
#define BLE_STACK_OPERATION_H

#include "State.h"

class BLE_Stack_Operation : public State
{
public:
    BLE_Stack_Operation();
    virtual ~BLE_Stack_Operation();

    void run() override;
};

#endif
