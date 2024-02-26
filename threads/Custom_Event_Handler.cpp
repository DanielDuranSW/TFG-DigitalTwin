#include "Custom_Event_Handler.h"

Custom_Event_Handler::Custom_Event_Handler() {}

Custom_Event_Handler::~Custom_Event_Handler() {}

void Custom_Event_Handler::run()
{
    pthread_mutex_lock(&mtx);
    // Lógica de Custom_Event_Handler
    sleep(1);
    printf("El estado es: %d\n", currentStage);
    State::nextStage();
    pthread_mutex_unlock(&mtx);
}
