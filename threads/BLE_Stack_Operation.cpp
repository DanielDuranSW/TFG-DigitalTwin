// BLE_Stack_Operation.cpp
#include "BLE_Stack_Operation.h"

BLE_Stack_Operation::BLE_Stack_Operation(DMAMonitor *dmaMonitor)
{
    // this->_id = id;
    this->_dmaMonitor = dmaMonitor;
}

BLE_Stack_Operation::~BLE_Stack_Operation() {}

void BLE_Stack_Operation::run()
{
    _dmaMonitor->BLE_Stack_Operation();
    // _dmaMonitor->incrementSharedCounter("BLE Stack Operation");
}
