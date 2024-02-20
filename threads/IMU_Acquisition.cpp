#include "IMU_Acquisition.h"

IMU_Acquisition::IMU_Acquisition(DMAMonitor *dmaMonitor)
{
    // this->_id = id;
    this->_dmaMonitor = dmaMonitor;
}

IMU_Acquisition::~IMU_Acquisition() {}

void IMU_Acquisition::run()
{
    _dmaMonitor->IMU_Acquisition();
    // _dmaMonitor->incrementSharedCounter("FSR Acquisition");
}
