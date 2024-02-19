// FSR_Acquisition.h
#ifndef FSR_ACQUISITION_H
#define FSR_ACQUISITION_H

#include "../TFG-DigitalTwin/dma_monitor.h"

class FSR_Acquisition
{
private:
    DMAMonitor *_dmaMonitor;

public:
    FSR_Acquisition(DMAMonitor *dmaMonitor);
    ~FSR_Acquisition();

    void run();
};

#endif
