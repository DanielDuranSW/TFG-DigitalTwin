#include "Custom_Event_Handler.h"

Custom_Event_Handler::Custom_Event_Handler() {}

Custom_Event_Handler::~Custom_Event_Handler() {}

void Custom_Event_Handler::run()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 5)
    {
        pthread_cond_wait(&cv_custom, &mtx);
    }
    // Lógica de Custom_Event_Handler
    printf("Custom_Event_Handler\n, con: %d\n", currentStage);
    sleep(1);
    State::nextStage();
    pthread_mutex_unlock(&mtx);
}
