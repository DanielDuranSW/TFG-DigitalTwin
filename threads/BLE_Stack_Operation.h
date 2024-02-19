// FSR_Acquisition.h
#ifndef BLE_STACK_OPERATION_H
#define BLE_STACK_OPERATION_H

#include "../TFG-DigitalTwin/dma_monitor.h"

class BLE_Stack_Operation
{
private:
    int _id;
    DMAMonitor *_dmaMonitor;

public:
    BLE_Stack_Operation(DMAMonitor *monitor);
    ~BLE_Stack_Operation();

    void run();
};

#endif
