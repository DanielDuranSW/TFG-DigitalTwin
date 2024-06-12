// Energy_Saving.cpp
#include "Energy_Saving.h"

void *energy_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;
    Resource *resource = &(args->resource);
    CSVReader *csvReaderFSR = args->csvReaderFSR;
    CSVReader *csvReaderIMU = args->csvReaderIMU;

    while (!terminateFlag)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 4)
        {
            state->waitCondition();
        }

        stateSignalHandler->onWorking("Energy", true);
        // printf("Energy_Saving ejecutando...\n");

        usleep(STATE_GENERAL_DURATION * PERCENTAGE_ENERGY_DURATION);

        // Aqui se debe dormir hasta que el hilo RTC lo despierte
        // Notificar al hilo RTC y esperar
        resource->signalCondition();
        resource->unlockMutex();
        resource->lockMutex();
        resource->waitCondition();
        resource->unlockMutex();

        stateSignalHandler->onWorking("Energy", false);

        INTENSITY_CONSUMED += STATE_ENERGY_INTENSITY;
        stateSignalHandler->intensityToChange(INTENSITY_CONSUMED);

        // printf("Energy_Saving terminado\n");

        state->setCurrentStage(5);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
