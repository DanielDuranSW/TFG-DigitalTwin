// BLE_Stack_Operation.cpp
#include "BLE_Stack_Operation.h"

BLE_Stack_Operation::BLE_Stack_Operation() {}

BLE_Stack_Operation::~BLE_Stack_Operation() {}

void BLE_Stack_Operation::run()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 4)
    {
        pthread_cond_wait(&cv_ble, &mtx);
    }
    // Lógica de BLE_Stack_Operation
    State::nextStage();
    pthread_mutex_unlock(&mtx);
}
