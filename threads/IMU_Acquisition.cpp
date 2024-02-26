#include "IMU_Acquisition.h"

IMU_Acquisition::IMU_Acquisition() {}

IMU_Acquisition::~IMU_Acquisition() {}

void IMU_Acquisition::run()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 1)
    {
        pthread_cond_wait(&cv_imu, &mtx);
    }
    // Lógica de IMU_Acquisition
    printf("IMU_Acquisition\n, con: %d\n", currentStage);
    sleep(1);
    State::nextStage();
    pthread_mutex_unlock(&mtx);
}
