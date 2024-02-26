#include "RAM_Operation.h"

RAM_Operation::RAM_Operation() {}

RAM_Operation::~RAM_Operation() {}

void RAM_Operation::run()
{
    pthread_mutex_lock(&mtx);
    // Lógica de RAM_Operation
    sleep(1);
    printf("El estado es: %d\n", currentStage);
    State::nextStage();
    pthread_mutex_unlock(&mtx);
}
