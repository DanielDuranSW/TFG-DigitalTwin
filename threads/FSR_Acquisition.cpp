// FSR_Acquisition.cpp
#include "FSR_Acquisition.h"

FSR_Acquisition::FSR_Acquisition() {}

FSR_Acquisition::~FSR_Acquisition() {}

void FSR_Acquisition::run()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 0)
    {
        pthread_cond_wait(&cv_fsr, &mtx);
    }
    // Lógica de FSR_Acquisition
    printf("FSR_Acquisition\n, con: %d\n", currentStage);
    sleep(1);
    State::nextStage();
    pthread_mutex_unlock(&mtx);
}
