#include "RAM_Operation.h"

RAM_Operation::RAM_Operation(DMAMonitor *dmaMonitor)
{
    // this->_id = id;
    this->_dmaMonitor = dmaMonitor;
}

RAM_Operation::~RAM_Operation() {}

void RAM_Operation::run()
{
    _dmaMonitor->RAM_Operation();
    // _dmaMonitor->incrementSharedCounter("RAM Operation");
}
