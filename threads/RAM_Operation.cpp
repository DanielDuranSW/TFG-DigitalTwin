// RAM_Operation.cpp
#include "RAM_Operation.h"

RAM_Operation::RAM_Operation(
    pthread_cond_t *cv_ram, pthread_mutex_t *mtx_threads)
{
    this->cv_ram = *cv_ram;
    this->mtx_threads = *mtx_threads;
}

RAM_Operation::~RAM_Operation() {}

void RAM_Operation::run()
{
    pthread_mutex_lock(&mtx_threads);

    printf("RAM_Operation espera signal\n");
    pthread_cond_wait(&cv_ram, &mtx_threads);
    printf("RAM_Operation acepta signal signal\n");

    // Lógica de RAM_Operation
    // ram.test();
    printf("RAM_Operation, con: %d\n", currentStage);
    sleep(1);
    pthread_mutex_unlock(&mtx_threads);
}

void *RAM_Operation::threadFunction(void *arg)
{
    RAM_Operation *fsrAcquisitionThreadObj = static_cast<RAM_Operation *>(arg);
    while (true)
    {
        fsrAcquisitionThreadObj->run();
    }
    return NULL;
}
