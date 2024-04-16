// RAM_Operation.cpp
#include "RAM_Operation.h"

void *ram_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;

    while (true)
    {
        args->state.lockMutex();
        while (args->state.getCurrentStage() != 2)
        {
            args->state.waitCondition();
        }
        stateSignalHandler->onWorking("Ram",true);
        printf("RAM_Operation ejecutando...\n");
        ram_function(args);
        printf("RAM_Operation terminado\n");
        stateSignalHandler->onWorking("Ram",false);
        args->state.setCurrentStage(3);
        args->state.broadcastCondition();
        args->state.unlockMutex();
    }
    pthread_exit(NULL);
}

void ram_function(Instances *args)
{
    args->ram.add(1);
    sleep(1);
}

