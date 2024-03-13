// Energy_Saving.cpp
#include "Energy_Saving.h"

Energy_Saving::Energy_Saving() {}

Energy_Saving::~Energy_Saving() {}

void Energy_Saving::run()
{
    pthread_mutex_lock(&mtx_threads);
    while (currentStage != 4)
    {
        printf("Energy_Saving espera signal\n");
        pthread_cond_wait(&cv_energy, &mtx_threads);
    }
    // Lógica de Energy_Saving
    printf("Energy_Saving, con: %d\n", currentStage);
    sleep(3);
    pthread_mutex_unlock(&mtx_threads);
}
