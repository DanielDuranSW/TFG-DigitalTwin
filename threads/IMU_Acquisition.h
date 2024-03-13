#ifndef IMU_ACQUISITION_H
#define IMU_ACQUISITION_H

#include "State.h"

class IMU_Acquisition : public State
{
public:
    IMU_Acquisition(
        pthread_cond_t *cv_imu, pthread_mutex_t *mtx_threads);
    ~IMU_Acquisition();

    void run();
    static void *threadFunction(void *arg);
};

#endif
