#ifndef CUSTOM_EVENT_HANDLER_H
#define CUSTOM_EVENT_HANDLER_H

#include "../TFG-DigitalTwin/dma_monitor.h"

class Custom_Event_Handler
{
private:
    DMAMonitor *dmaMonitor;

public:
    Custom_Event_Handler(DMAMonitor *monitor);
    void run();
};

#endif
