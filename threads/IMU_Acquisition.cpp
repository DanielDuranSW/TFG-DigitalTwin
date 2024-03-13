// IMU_Acquisition.cpp
#include "IMU_Acquisition.h"

IMU_Acquisition::IMU_Acquisition(pthread_cond_t *cv_imu, pthread_mutex_t *mtx_threads)
{
    this->cv_imu = *cv_imu;
    this->mtx_threads = *mtx_threads;
}

IMU_Acquisition::~IMU_Acquisition() {}

void IMU_Acquisition::run()
{
    pthread_mutex_lock(&mtx_threads);

    printf("IMU_Acquisition espera signal\n");
    pthread_cond_wait(&cv_imu, &mtx_threads);
    printf("IMU_Acquisition acepta signal signal\n");

    // Lógica de IMU_Acquisition
    printf("IMU_Acquisition, con: %d\n", currentStage);
    sleep(1);
    pthread_mutex_unlock(&mtx_threads);
}

void *IMU_Acquisition::threadFunction(void *arg)
{
    IMU_Acquisition *imuAcquisitionThreadObj = static_cast<IMU_Acquisition *>(arg);
    while (true)
    {
        imuAcquisitionThreadObj->run();
    }
    return NULL;
}