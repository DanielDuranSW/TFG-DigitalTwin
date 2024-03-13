// FSR_Acquisition.h
#ifndef FSR_ACQUISITION_H
#define FSR_ACQUISITION_H

#include "State.h"

class FSR_Acquisition : public State
{
public:
    FSR_Acquisition(
        pthread_cond_t *cv_fsr, pthread_mutex_t *mtx_threads);

    ~FSR_Acquisition();

    void run();
    static void *threadFunction(void *arg);
};

#endif
