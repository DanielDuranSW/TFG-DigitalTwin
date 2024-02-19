// FSR_Acquisition.h
#ifndef BLE_STACK_OPERATION_H
#define BLE_STACK_OPERATION_H

#include "../TFG-DigitalTwin/dma_monitor.h"

class BLE_Stack_Operation
{
private:
    DMAMonitor *dmaMonitor;

public:
    BLE_Stack_Operation(DMAMonitor *monitor);
    void run();
};

#endif
