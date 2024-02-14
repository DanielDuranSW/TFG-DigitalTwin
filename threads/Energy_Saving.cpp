#include "Energy_Saving.h"
#include "../TFG-DigitalTwin/dma.h"
#include <unistd.h>

void *Energy_Saving(void *arg)
{
    while (true)
    {
        incrementarDMA();
        // Lógica
        sleep(1);
    }
    return nullptr;
}
