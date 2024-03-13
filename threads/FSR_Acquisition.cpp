// FSR_Acquisition.cpp
#include "FSR_Acquisition.h"

void *fsr_run(void *arg)
{
    State *state = static_cast<State *>(arg);
    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 0)
        {
            state->waitCondition();
        }

        printf("FSR_Acquisition ejecutando...\n");
        sleep(1); // Simulación de trabajo
        printf("FSR_Acquisition terminado\n");

        state->setCurrentStage(1);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}