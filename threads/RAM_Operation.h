#ifndef RAM_OPERATION_H
#define RAM_OPERATION_H

#include "State.h"
#include "resources/RAM.h"

class RAM_Operation : public State
{
private:
    RAM ram;

public:
    RAM_Operation(
        pthread_cond_t *cv_ram, pthread_mutex_t *mtx_threads);
    ~RAM_Operation();

    void run();
    static void *threadFunction(void *arg);
};

#endif
