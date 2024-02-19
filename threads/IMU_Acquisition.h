#ifndef IMU_ACQUISITION_H
#define IMU_ACQUISITION_H

#include "../TFG-DigitalTwin/dma_monitor.h"

class IMU_Acquisition
{
private:
    DMAMonitor *dmaMonitor;

public:
    IMU_Acquisition(DMAMonitor *monitor);
    void run();
};

#endif
