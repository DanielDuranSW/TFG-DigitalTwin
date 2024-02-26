#include "Energy_Saving.h"

Energy_Saving::Energy_Saving() {}

Energy_Saving::~Energy_Saving() {}

void Energy_Saving::run()
{
    pthread_mutex_lock(&mtx);
    // Lógica de Energy_Saving
    sleep(1);
    printf("El estado es: %d\n", currentStage);
    State::nextStage();
    pthread_mutex_unlock(&mtx);
}
