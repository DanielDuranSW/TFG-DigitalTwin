// Custom_Event_Handler.cpp
#include "Custom_Event_Handler.h"

void *custom_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;

    while (!terminateFlag)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 5)
        {
            state->waitCondition();
        }
        stateSignalHandler->onWorking("Custom", true);
        // printf("Custom_Event_Handler ejecutando...\n");

        if (realSimulation)
        {
            usleep(STATE_CUSTOM_DURATION);
        }
        else
        {
            usleep(STATE_GENERAL_DURATION);
        }

        INTENSITY_CONSUMED += STATE_GENERAL_INTENSITY;
        stateSignalHandler->intensityToChange(INTENSITY_CONSUMED);

        // printf("Custom_Event_Handler terminado\n");
        stateSignalHandler->onWorking("Custom", false);

        state->setCurrentStage(0);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
