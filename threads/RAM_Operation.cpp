// RAM_Operation.cpp
#include "RAM_Operation.h"

RAM_Operation::RAM_Operation() {}

RAM_Operation::~RAM_Operation() {}

void RAM_Operation::run()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 2)
    {
        printf("RAM_Operation espera signal\n");
        pthread_cond_wait(&cv_ram, &mtx);
    }
    // Lógica de RAM_Operation
    printf("RAM_Operation, con: %d\n", currentStage);
    sleep(3);
    pthread_mutex_unlock(&mtx);
}
