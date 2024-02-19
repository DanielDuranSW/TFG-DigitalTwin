#include "Custom_Event_Handler.h"

Custom_Event_Handler::Custom_Event_Handler(DMAMonitor *monitor) {}

void Custom_Event_Handler::run()
{
    dmaMonitor->Custom_Event_Handler();
    // lógica
}
