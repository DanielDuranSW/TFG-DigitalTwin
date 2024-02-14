#include "RAM_Operation.h"
#include "../TFG-DigitalTwin/dma.h"
#include <unistd.h>

void *RAM_Operation(void *arg)
{
    while (true)
    {
        incrementarDMA();
        // Lógica
        sleep(1);
    }
    return nullptr;
}
