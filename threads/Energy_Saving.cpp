// Energy_Saving.cpp
#include "Energy_Saving.h"

Energy_Saving::Energy_Saving(
    pthread_cond_t *cv_energy, pthread_mutex_t *mtx_threads)
{
    this->cv_energy = *cv_energy;
    this->mtx_threads = *mtx_threads;
}

Energy_Saving::~Energy_Saving() {}

void Energy_Saving::run()
{
    pthread_mutex_lock(&mtx_threads);

    printf("Energy_Saving espera signal\n");
    pthread_cond_wait(&cv_energy, &mtx_threads);
    printf("Energy_Saving acepta signal signal\n");

    // Lógica de Energy_Saving
    printf("Energy_Saving, con: %d\n", currentStage);
    sleep(3);
    pthread_mutex_unlock(&mtx_threads);
}

void *Energy_Saving::threadFunction(void *arg)
{
    Energy_Saving *fsrAcquisitionThreadObj = static_cast<Energy_Saving *>(arg);
    while (true)
    {
        fsrAcquisitionThreadObj->run();
    }
    return NULL;
}