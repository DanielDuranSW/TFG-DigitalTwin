#include "RAM_Operation.h"

RAM_Operation::RAM_Operation() {}

RAM_Operation::~RAM_Operation() {}

void RAM_Operation::run()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 2)
    {
        pthread_cond_wait(&cv_ram, &mtx);
    }
    // Lógica de RAM_Operation
    printf("RAM_Operation\n, con: %d\n", currentStage);
    sleep(1);
    State::nextStage();
    pthread_mutex_unlock(&mtx);
}
