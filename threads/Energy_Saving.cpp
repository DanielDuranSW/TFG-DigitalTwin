// Energy_Saving.cpp
#include "Energy_Saving.h"

void *energy_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;
    Resource *resource = &(args->resource);

    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 4)
        {
            state->waitCondition();
        }

        stateSignalHandler->onWorking("Energy", true);
        printf("Energy_Saving ejecutando...\n");

        // Aqui se debe dormir hasta que el hilo RTC lo despierte
        // Notificar al hilo RTC y esperar
        resource->signalCondition();
        resource->unlockMutex();
        resource->lockMutex();
        resource->waitCondition();
        resource->unlockMutex();
        // sleep(2);
        usleep(STATE_GENERAL_DURATION); // Simulación de trabajo

        INTENSITY_CONSUMED += 0.001;
        stateSignalHandler->intensityToChange(INTENSITY_CONSUMED);

        printf("Energy_Saving terminado\n");
        stateSignalHandler->onWorking("Energy", false);

        state->setCurrentStage(5);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
