// RAM_Operation.cpp
#include "RAM_Operation.h"

void *ram_run(void *arg)
{
    State *state = static_cast<State *>(arg);
    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 2)
        {
            state->waitCondition();
        }

        printf("RAM_Operation ejecutando...\n");
        sleep(1); // Simulación de trabajo
        printf("RAM_Operation terminado\n");

        state->setCurrentStage(3);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
