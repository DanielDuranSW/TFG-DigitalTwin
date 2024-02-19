#include "BLE_Stack_Operation.h"

BLE_Stack_Operation::BLE_Stack_Operation(DMAMonitor *monitor) {}

void BLE_Stack_Operation::run()
{
    dmaMonitor->BLE_Stack_Operation();
    // lógica
}
