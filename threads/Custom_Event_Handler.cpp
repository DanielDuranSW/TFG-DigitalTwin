#include "Custom_Event_Handler.h"
#include "../TFG-DigitalTwin/dma.h"
#include <unistd.h>

void *Custom_Event_Handler(void *arg)
{
    while (true)
    {
        incrementarDMA();
        // Lógica
        sleep(1);
    }
    return nullptr;
}
