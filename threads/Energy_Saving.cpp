// Energy_Saving.cpp
#include "Energy_Saving.h"

void *energy_run(void *arg)
{
    State *state = static_cast<State *>(arg);
    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 4)
        {
            state->waitCondition();
        }

        printf("Energy_Saving ejecutando...\n");
        sleep(1); // Simulación de trabajo
        printf("Energy_Saving terminado\n");

        state->setCurrentStage(5);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
