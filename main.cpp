#include <iostream>
#include <thread>
#include "dma_monitor.h"
#include "threads/BLE_Stack_Operation.h"
#include "threads/Custom_Event_Handler.h"
#include "threads/FSR_Acquisition.h"
#include "threads/IMU_Acquisition.h"
#include "threads/RAM_Operation.h"
#include "threads/Energy_Saving.h"

int main()
{
    DMAMonitor dmaMonitor;

    // Creación de instancias de cada operación.
    FSR_Acquisition fsr(&dmaMonitor);
    IMU_Acquisition imu(&dmaMonitor);
    RAM_Operation ram(&dmaMonitor);
    BLE_Stack_Operation ble(&dmaMonitor);
    Energy_Saving energy(&dmaMonitor);
    Custom_Event_Handler custom(&dmaMonitor);

    // Inicio de cada operación en su propio hilo.
    std::thread fsrThread([&]()
                          { fsr.run(); });
    std::thread imuThread([&]()
                          { imu.run(); });
    std::thread ramThread([&]()
                          { ram.run(); });
    std::thread bleThread([&]()
                          { ble.run(); });
    std::thread energyThread([&]()
                             { energy.run(); });
    std::thread customThread([&]()
                             { custom.run(); });

    // Espera a que todos los hilos terminen.
    fsrThread.join();
    imuThread.join();
    ramThread.join();
    bleThread.join();
    energyThread.join();
    customThread.join();

    return 0;
}
