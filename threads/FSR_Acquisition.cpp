// FSR_Acquisition.cpp
#include "FSR_Acquisition.h"

FSR_Acquisition::FSR_Acquisition() {}

FSR_Acquisition::~FSR_Acquisition() {}

void FSR_Acquisition::run()
{
    pthread_mutex_lock(&mtx);
    // Lógica de FSR_Acquisition
    sleep(1);
    printf("El estado es: %d\n", currentStage);
    State::nextStage();
    pthread_mutex_unlock(&mtx);
}
