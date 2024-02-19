#ifndef IMU_ACQUISITION_H
#define IMU_ACQUISITION_H

#include "../TFG-DigitalTwin/dma_monitor.h"

class IMU_Acquisition
{
private:
    DMAMonitor *_dmaMonitor;

public:
    IMU_Acquisition(DMAMonitor *monitor);
    ~IMU_Acquisition();

    void run();
};

#endif
