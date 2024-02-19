#ifndef RAM_OPERATION_H
#define RAM_OPERATION_H

#include "../TFG-DigitalTwin/dma_monitor.h"

class RAM_Operation
{
private:
    DMAMonitor *dmaMonitor;

public:
    RAM_Operation(DMAMonitor *monitor);
    void run();
};

#endif
