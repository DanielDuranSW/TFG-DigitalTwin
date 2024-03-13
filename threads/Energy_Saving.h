#ifndef ENERGY_SAVING_H
#define ENERGY_SAVING_H

#include "State.h"

class Energy_Saving : public State
{
public:
    Energy_Saving(pthread_cond_t *cv_energy, pthread_mutex_t *mtx_threads);
    virtual ~Energy_Saving();

    void run();
    static void *threadFunction(void *arg);
};

#endif
