// FSR_Acquisition.cpp
#include "FSR_Acquisition.h"

FSR_Acquisition::FSR_Acquisition(DMAMonitor *dmaMonitor)
{
    // this->_id = id;
    this->_dmaMonitor = dmaMonitor;
}

FSR_Acquisition::~FSR_Acquisition() {}

void FSR_Acquisition::run()
{
    _dmaMonitor->FSR_Acquisition();
    _dmaMonitor->incrementSharedCounter("FSR Acquisition");
}
