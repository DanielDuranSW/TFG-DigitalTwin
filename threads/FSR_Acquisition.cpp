#include "FSR_Acquisition.h"

FSR_Acquisition::FSR_Acquisition(DMAMonitor *monitor) {}

void FSR_Acquisition::run()
{
    dmaMonitor->FSR_Acquisition();
    // lógica
}
