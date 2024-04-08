// FSR_Acquisition.cpp
#include "FSR_Acquisition.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/StateSignalHandler.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/ThreadsData.h"

void *fsr_run(void *arg)
{
    Instances *args = static_cast<Instances*>(arg);
    State *state = &(args->state);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;

    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 0)
        {
            state->waitCondition();
        }

        stateSignalHandler->onFsrWorking(true);
        printf("FSR_Acquisition ejecutando...\n");
        sleep(1); // Simulación de trabajo
        printf("FSR_Acquisition terminado\n");
        stateSignalHandler->onFsrWorking(false);

        state->setCurrentStage(1);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
