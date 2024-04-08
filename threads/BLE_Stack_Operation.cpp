// BLE_Stack_Operation.cpp
#include "BLE_Stack_Operation.h"

void *ble_run(void *arg)
{
    Instances *args = static_cast<Instances*>(arg);
    State *state = &(args->state);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;

    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 3)
        {
            state->waitCondition();
        }
        stateSignalHandler->onWorking("Ble",true);
        printf("BLE_Stack_Operation ejecutando...\n");
        sleep(1); // Simulación de trabajo

        printf("BLE_Stack_Operation terminado\n");
        stateSignalHandler->onWorking("Ble",false);
        state->setCurrentStage(4);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
