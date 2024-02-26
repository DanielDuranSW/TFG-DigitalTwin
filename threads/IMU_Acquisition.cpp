#include "IMU_Acquisition.h"

IMU_Acquisition::IMU_Acquisition() {}

IMU_Acquisition::~IMU_Acquisition() {}

void IMU_Acquisition::run()
{
    pthread_mutex_lock(&mtx);
    // Lógica de IMU_Acquisition
    sleep(1);
    printf("El estado es: %d\n", currentStage);
    State::nextStage();
    pthread_mutex_unlock(&mtx);
}
