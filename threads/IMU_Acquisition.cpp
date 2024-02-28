// IMU_Acquisition.cpp
#include "IMU_Acquisition.h"

IMU_Acquisition::IMU_Acquisition() {}

IMU_Acquisition::~IMU_Acquisition() {}

void IMU_Acquisition::run()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 1)
    {
        printf("IMU_Acquisition espera signal\n");
        pthread_cond_wait(&cv_imu, &mtx);
    }
    // Lógica de IMU_Acquisition
    printf("IMU_Acquisition, con: %d\n", currentStage);
    sleep(3);
    pthread_mutex_unlock(&mtx);
}
