#include "Insole.h"
#include <iostream>
#include <pthread.h>
#include "State.h"
#include "threads/BLE_Stack_Operation.h"
#include "threads/Custom_Event_Handler.h"
#include "threads/FSR_Acquisition.h"
#include "threads/IMU_Acquisition.h"
#include "threads/RAM_Operation.h"
#include "threads/Energy_Saving.h"

class OrchestratorMain
{
public:
    OrchestratorMain();
    ~OrchestratorMain();

    void start();

private:
    // Insole *insole; // Puntero a Insole
    // int currentStage;
};
