// main.cpp
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "threads/BLE_Stack_Operation.h"
#include "threads/Custom_Event_Handler.h"
#include "threads/FSR_Acquisition.h"
#include "threads/IMU_Acquisition.h"
#include "threads/RAM_Operation.h"
#include "threads/Energy_Saving.h"

#include "ThreadsData.h"

int main()
{
    State state;
    RAM ram;

    Instances argsInstance;
    argsInstance.state = state;
    argsInstance.ram = ram;

    pthread_t fsrAcquisitionThread;
    pthread_t imuAcquisitionThread;
    pthread_t ramOperationThread;
    pthread_t bleStackThread;
    pthread_t energySavingThread;
    pthread_t customEventHandlerThread;

    pthread_t ramToFlashThread;

    // Crear los hilos
    pthread_create(&fsrAcquisitionThread, NULL, fsr_run, &argsInstance.state);
    pthread_create(&imuAcquisitionThread, NULL, imu_run, &argsInstance.state);
    pthread_create(&ramOperationThread, NULL, ram_run, &argsInstance);
    pthread_create(&bleStackThread, NULL, ble_run, &argsInstance.state);
    pthread_create(&energySavingThread, NULL, energy_run, &argsInstance.state);
    pthread_create(&customEventHandlerThread, NULL, custom_run, &argsInstance.state);

    pthread_create(&ramToFlashThread, NULL, ram_checkAndConsume, &argsInstance.ram);

    // Esperar a que todos los hilos terminen
    pthread_join(fsrAcquisitionThread, NULL);
    pthread_join(imuAcquisitionThread, NULL);
    pthread_join(ramOperationThread, NULL);
    pthread_join(bleStackThread, NULL);
    pthread_join(energySavingThread, NULL);
    pthread_join(customEventHandlerThread, NULL);

    pthread_join(ramToFlashThread, NULL);

    return 0;
}