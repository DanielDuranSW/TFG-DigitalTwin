#include "FSR_Acquisition.h"
#include "../TFG-DigitalTwin/dma.h"
#include <unistd.h>

void *FSR_Acquisition(void *arg)
{
    while (true)
    {
        incrementarDMA();
        // Lógica
        sleep(1);
    }
    return nullptr;
}
