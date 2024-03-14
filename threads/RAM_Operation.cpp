// RAM_Operation.cpp
#include "RAM_Operation.h"
#include "ThreadsData.h"

void *ram_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    while (true)
    {
        args->state.lockMutex();
        while (args->state.getCurrentStage() != 2)
        {
            args->state.waitCondition();
        }

        printf("RAM_Operation ejecutando...\n");
        ram_function(&args->ram); // Simulación de trabajo
        printf("RAM_Operation terminado\n");

        args->state.setCurrentStage(3);
        args->state.broadcastCondition();
        args->state.unlockMutex();
    }
    pthread_exit(NULL);
}

void ram_function(RAM *ram)
{
    // RAM *ram = new RAM();
    // ram->test();
    ram->add(1);
    sleep(1);
}