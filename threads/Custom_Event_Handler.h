#ifndef CUSTOM_EVENT_HANDLER_H
#define CUSTOM_EVENT_HANDLER_H

#include "State.h"

class Custom_Event_Handler : public State
{
public:
    Custom_Event_Handler(
        pthread_cond_t *cv_custom, pthread_mutex_t *mtx_threads);
    virtual ~Custom_Event_Handler();

    void run();
    static void *threadFunction(void *arg);
};

#endif
