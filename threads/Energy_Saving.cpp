#include "Energy_Saving.h"

Energy_Saving::Energy_Saving() {}

Energy_Saving::~Energy_Saving() {}

void Energy_Saving::run()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 3)
    {
        pthread_cond_wait(&cv_energy, &mtx);
    }
    // Lógica de BLE_Stack_Operation
    printf("Energy_Saving, con: %d\n", currentStage);
    sleep(1);
    State::nextStage();
    pthread_mutex_unlock(&mtx);
}
