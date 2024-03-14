// RAM_Operation.cpp
#include "RAM_Operation.h"

RAM *ram = new RAM();

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
        ram_function(); // Simulación de trabajo
        printf("RAM_Operation terminado\n");

        state->setCurrentStage(3);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}

void ram_function()
{
    // RAM *ram = new RAM();
    // ram->test();
    ram->add(1);
    sleep(1);
}