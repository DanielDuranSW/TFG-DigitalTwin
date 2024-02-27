// FSR_Acquisition.cpp
#include "FSR_Acquisition.h"

FSR_Acquisition::FSR_Acquisition() {}

FSR_Acquisition::~FSR_Acquisition() {}

void FSR_Acquisition::run()
{

    pthread_mutex_lock(&mtx);
    while (currentStage != 0)
    {
        printf("FSR_Acquisition espera signal\n");
        pthread_cond_wait(&cv_fsr, &mtx);
    }
    // Lógica de FSR_Acquisition
    printf("FSR_Acquisition, con: %d\n", currentStage);
    sleep(3);
    // State::nextStage();
    pthread_mutex_unlock(&mtx);
}
