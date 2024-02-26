#ifndef INSOLE_H
#define INSOLE_H

#include <pthread.h>
#include "State.h"
class Insole
{
    // State state// Composición: Insole contiene un State

public:
    Insole();
    ~Insole();

    // void signalNextStage();

private:
    friend class OrchestratorMain; // Permitir acceso a OrchestratorMain (asociación de clases)
};

#endif
