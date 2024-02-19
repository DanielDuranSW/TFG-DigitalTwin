#ifndef ENERGY_SAVING_H
#define ENERGY_SAVING_H

#include "../TFG-DigitalTwin/dma_monitor.h"

class Energy_Saving
{
private:
    DMAMonitor *dmaMonitor;

public:
    Energy_Saving(DMAMonitor *monitor);
    void run();
};

#endif