#include "Custom_Event_Handler.h"

Custom_Event_Handler::Custom_Event_Handler(DMAMonitor *dmaMonitor)
{
    // this->_id = id;
    this->_dmaMonitor = dmaMonitor;
}

Custom_Event_Handler::~Custom_Event_Handler() {}

void Custom_Event_Handler::run()
{
    _dmaMonitor->Custom_Event_Handler();
    // _dmaMonitor->incrementSharedCounter("Custom Event Handler");
}
