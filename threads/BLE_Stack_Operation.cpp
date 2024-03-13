// BLE_Stack_Operation.cpp
#include "BLE_Stack_Operation.h"

BLE_Stack_Operation::BLE_Stack_Operation() {}

BLE_Stack_Operation::~BLE_Stack_Operation() {}

void BLE_Stack_Operation::run()
{
    // waitThreadsReady();

    pthread_mutex_lock(&mtx_threads);
    while (currentStage != 3)
    {
        printf("BLE_Stack_Operation espera signal\n");
        pthread_cond_wait(&cv_ble, &mtx_threads);
    }
    // Lógica de BLE_Stack_Operation
    printf("BLE_Stack_Operation, con: %d\n", currentStage);
    sleep(1);
    pthread_mutex_unlock(&mtx_threads);
}

// void BLE_Stack_Operation::waitThreadsReady()
// {
//     pthread_mutex_lock(&startMutex);
//     while (readyCount < totalThreads)
//     {
//         pthread_cond_wait(&startCond, &startMutex); // Espera hasta que todos los hilos estén listos
//     }
//     pthread_mutex_unlock(&startMutex);
// }