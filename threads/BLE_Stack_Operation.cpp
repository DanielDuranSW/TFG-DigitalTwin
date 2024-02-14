#include "BLE_Stack_Operation.h"
#include "../TFG-DigitalTwin/dma.h"
#include <unistd.h>

void *BLE_Stack_Operation(void *arg)
{
    while (true)
    {
        incrementarDMA();
        // Lógica
        sleep(1);
    }
    return nullptr;
}
