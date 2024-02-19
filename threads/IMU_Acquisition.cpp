#include "IMU_Acquisition.h"

IMU_Acquisition::IMU_Acquisition(DMAMonitor *monitor) {}

void IMU_Acquisition::run()
{
    dmaMonitor->IMU_Acquisition();
    // lógica
}
