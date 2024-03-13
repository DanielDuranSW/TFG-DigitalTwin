// Custom_Event_Handler.cpp
#include "Custom_Event_Handler.h"

void *custom_run(void *arg)
{
    State *state = static_cast<State *>(arg);
    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 5)
        {
            state->waitCondition();
        }

        printf("Custom_Event_Handler ejecutando...\n");
        sleep(1); // Simulación de trabajo
        printf("Custom_Event_Handler terminado\n");

        state->setCurrentStage(0);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
