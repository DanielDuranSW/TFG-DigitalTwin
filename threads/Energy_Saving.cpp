// Energy_Saving.cpp
#include "Energy_Saving.h"

void *energy_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;

    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 4)
        {
            state->waitCondition();
        }

        stateSignalHandler->onWorking("Energy", true);
        printf("Energy_Saving ejecutando...\n");
        usleep(STATE_GENERAL_DURATION); // Simulación de trabajo
        printf("Energy_Saving terminado\n");
        stateSignalHandler->onWorking("Energy", false);

        state->setCurrentStage(5);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
