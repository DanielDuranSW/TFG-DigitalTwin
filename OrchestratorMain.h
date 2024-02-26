#include "Insole.h"
#include <iostream>

class OrchestratorMain
{
public:
    OrchestratorMain();
    ~OrchestratorMain();

    void OrchestratorMain::start();

private:
    Insole *insole; // Puntero a Insole
    int currentStage;
};
