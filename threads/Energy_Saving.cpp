#include "Energy_Saving.h"

Energy_Saving::Energy_Saving(DMAMonitor *dmaMonitor)
{
    // this->_id = id;
    this->_dmaMonitor = dmaMonitor;
}

Energy_Saving::~Energy_Saving() {}

void Energy_Saving::run()
{
    _dmaMonitor->Energy_Saving();
    _dmaMonitor->incrementSharedCounter("Energy Saving");
}
