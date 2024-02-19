#include "RAM_Operation.h"

RAM_Operation::RAM_Operation(DMAMonitor *monitor) {}

void RAM_Operation::run()
{
    dmaMonitor->RAM_Operation();
    // lógica
}
