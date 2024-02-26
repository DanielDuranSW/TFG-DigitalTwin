#ifndef CUSTOM_EVENT_HANDLER_H
#define CUSTOM_EVENT_HANDLER_H

#include "State.h"

class Custom_Event_Handler : public State
{
public:
    Custom_Event_Handler();
    virtual ~Custom_Event_Handler();

    void run() override;
};

#endif
