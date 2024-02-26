// OrchestratorMain.cpp
#include "OrchestratorMain.h"

#include "State.h"
#include "threads/BLE_Stack_Operation.h"
#include "threads/Custom_Event_Handler.h"
#include "threads/FSR_Acquisition.h"
#include "threads/IMU_Acquisition.h"
#include "threads/RAM_Operation.h"
#include "threads/Energy_Saving.h"

OrchestratorMain::OrchestratorMain() : currentStage(0)
{
    // insole = new Insole(); // Para asociación con Insole
}

OrchestratorMain::~OrchestratorMain()
{
    // delete insole; // Para asociación con Insole
}

void OrchestratorMain::start()
{
    while (true)
    {
        switch (State::currentStage)
        {

        case 0:
        {
            FSR_Acquisition fsr_acquisition;
            fsr_acquisition.run();
            break;
        }

        case 1:
        {
            IMU_Acquisition imu_acquisition;
            imu_acquisition.run();
            break;
        }
        case 2:
        {
            RAM_Operation ram_operation;
            ram_operation.run();
            break;
        }
        case 3:
        {
            BLE_Stack_Operation ble_stack_operation;
            ble_stack_operation.run();
            break;
        }
        case 4:
        {
            Energy_Saving energy_saving;
            energy_saving.run();
            break;
        }
        case 5:
        {
            Custom_Event_Handler custom_event_handler;
            custom_event_handler.run();
            break;
        }
        }
    }