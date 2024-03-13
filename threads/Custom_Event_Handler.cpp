// Custom_Event_Handler.cpp
#include "Custom_Event_Handler.h"

Custom_Event_Handler::Custom_Event_Handler() {}

Custom_Event_Handler::~Custom_Event_Handler() {}

void Custom_Event_Handler::run()
{
    pthread_mutex_lock(&mtx_threads);
    while (currentStage != 5)
    {
        printf("Custom_Event_Handler espera signal\n");
        pthread_cond_wait(&cv_custom, &mtx_threads);
    }
    printf("Custom_Event_Handler, con: %d\n", currentStage);
    sleep(1);
    // State::nextStage();
    pthread_mutex_unlock(&mtx_threads);
}
