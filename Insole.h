#ifndef INSOLE_H
#define INSOLE_H

#include <pthread.h>
#include <string>

class Insole
{
public:
    Insole();
    ~Insole();

private:
    friend class OrchestratorMain; // Permitir acceso a OrchestratorMain (asociación de clases)
};

#endif
