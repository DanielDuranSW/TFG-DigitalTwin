// Custom_Event_Handler.cpp
#include "Custom_Event_Handler.h"

Custom_Event_Handler::Custom_Event_Handler(
    pthread_cond_t *cv_custom, pthread_mutex_t *mtx_threads)
{
    this->cv_custom = *cv_custom;
    this->mtx_threads = *mtx_threads;
}

Custom_Event_Handler::~Custom_Event_Handler() {}

void Custom_Event_Handler::run()
{
    pthread_mutex_lock(&mtx_threads);

    printf("Custom_Event_Handler espera signal\n");
    pthread_cond_wait(&cv_custom, &mtx_threads);
    printf("Custom_Event_Handler acepta signal signal\n");

    printf("Custom_Event_Handler, con: %d\n", currentStage);
    sleep(1);
    // State::nextStage();
    pthread_mutex_unlock(&mtx_threads);
}

void *Custom_Event_Handler::threadFunction(void *arg)
{
    Custom_Event_Handler *customEventHandlerThreadObj = static_cast<Custom_Event_Handler *>(arg);
    while (true)
    {
        customEventHandlerThreadObj->run();
    }
    return NULL;
}
