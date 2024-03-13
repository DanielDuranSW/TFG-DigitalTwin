// BLE_Stack_Operation.h
#ifndef BLE_STACK_OPERATION_H
#define BLE_STACK_OPERATION_H

#include "State.h"

class BLE_Stack_Operation : public State
{
public:
    BLE_Stack_Operation(
        pthread_cond_t *cv_ble, pthread_mutex_t *mtx_threads);
    virtual ~BLE_Stack_Operation();

    void run();
    static void *threadFunction(void *arg);
};

#endif
