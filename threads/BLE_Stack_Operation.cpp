// BLE_Stack_Operation.cpp
#include "BLE_Stack_Operation.h"

void *ble_run(void *arg)
{
    State *state = static_cast<State *>(arg);
    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 3)
        {
            state->waitCondition();
        }

        printf("BLE_Stack_Operation ejecutando...\n");
        sleep(1); // Simulación de trabajo

        printf("BLE_Stack_Operation terminado\n");

        state->setCurrentStage(4);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
