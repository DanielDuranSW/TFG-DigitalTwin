// OrchestratorMain.cpp
// #include "OrchestratorMain.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "threads/BLE_Stack_Operation.h"
#include "threads/Custom_Event_Handler.h"
#include "threads/FSR_Acquisition.h"
#include "threads/IMU_Acquisition.h"
#include "threads/RAM_Operation.h"
#include "threads/Energy_Saving.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int current_stage = 0;

int main()
{
    pthread_t fsrAcquisitionThread;
    pthread_t imuAcquisitionThread;
    pthread_t ramOperationThread;
    pthread_t bleStackThread;
    pthread_t energySavingThread;
    pthread_t customEventHandlerThread;

    // Crear los hilos
    pthread_create(&fsrAcquisitionThread, NULL, fsr_function, NULL);
    pthread_create(&imuAcquisitionThread, NULL, imu_function, NULL);
    pthread_create(&ramOperationThread, NULL, ram_function, NULL);
    pthread_create(&bleStackThread, NULL, ble_function, NULL);
    pthread_create(&energySavingThread, NULL, energy_function, NULL);
    pthread_create(&customEventHandlerThread, NULL, custom_function, NULL);

    // Esperar a que todos los hilos terminen
    pthread_join(fsrAcquisitionThread, NULL);
    pthread_join(imuAcquisitionThread, NULL);
    pthread_join(ramOperationThread, NULL);
    pthread_join(bleStackThread, NULL);
    pthread_join(energySavingThread, NULL);
    pthread_join(customEventHandlerThread, NULL);

    return 0;
}
