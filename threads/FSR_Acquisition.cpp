// FSR_Acquisition.cpp
#include "FSR_Acquisition.h"

FSR_Acquisition::FSR_Acquisition(
    pthread_cond_t *cv_fsr, pthread_mutex_t *mtx_threads)
{
    this->cv_fsr = *cv_fsr;
    this->mtx_threads = *mtx_threads;
}

FSR_Acquisition::~FSR_Acquisition() {}

void FSR_Acquisition::run()
{
    pthread_mutex_lock(&mtx_threads);

    printf("FSR_Acquisition espera signal\n");
    pthread_cond_wait(&cv_fsr, &mtx_threads);
    printf("FSR_Acquisition acepta signal signal\n");

    // Lógica de FSR_Acquisition
    printf("FSR_Acquisition, con: %d\n", currentStage);
    sleep(1);
    pthread_mutex_unlock(&mtx_threads);
}

void *FSR_Acquisition::threadFunction(void *arg)
{
    FSR_Acquisition *fsrAcquisitionThreadObj = static_cast<FSR_Acquisition *>(arg);
    while (true)
    {
        fsrAcquisitionThreadObj->run();
    }
    return NULL;
}
