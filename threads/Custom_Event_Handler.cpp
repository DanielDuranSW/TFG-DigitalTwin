// Custom_Event_Handler.cpp
#include "Custom_Event_Handler.h"

void *custom_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;

    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 5)
        {
            state->waitCondition();
        }
        stateSignalHandler->onWorking("Rtc", false);
        stateSignalHandler->onWorking("Custom", true);
        printf("Custom_Event_Handler ejecutando...\n");
        usleep(STATE_GENERAL_DURATION); // Simulación de trabajo

        INTENSITY_CONSUMED += 0.1;
        stateSignalHandler->intensityToChange(INTENSITY_CONSUMED);

        printf("Custom_Event_Handler terminado\n");
        stateSignalHandler->onWorking("Custom", false);

        state->setCurrentStage(0);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
