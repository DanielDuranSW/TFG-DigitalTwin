// main.cpp
#include <iostream>
#include <pthread.h>
#include "State.h"
#include "OrchestratorMain.h"
#include "threads/BLE_Stack_Operation.h"
#include "threads/Custom_Event_Handler.h"
#include "threads/FSR_Acquisition.h"
#include "threads/IMU_Acquisition.h"
#include "threads/RAM_Operation.h"
#include "threads/Energy_Saving.h"
#include <cstdio>

static void *FSR_Acquisition_func(void *arg)
{
    FSR_Acquisition fsrAcquisition;
    fsrAcquisition.run();
    return NULL;
}

static void *IMU_Acquisition_func(void *arg)
{
    IMU_Acquisition imuAcquisition;
    imuAcquisition.run();
    return NULL;
}

static void *RAM_Operation_func(void *arg)
{
    RAM_Operation ramOperation;
    ramOperation.run();
    return NULL;
}

static void *BLE_Stack_Operation_func(void *arg)
{
    BLE_Stack_Operation bleStackOperation;
    bleStackOperation.run();
    return NULL;
}

static void *Energy_Saving_func(void *arg)
{
    Energy_Saving energySaving;
    energySaving.run();
    return NULL;
}

static void *Custom_Event_Handler_func(void *arg)
{
    Custom_Event_Handler customEventHandler;
    customEventHandler.run();
    return NULL;
}

int main()
{

    pthread_t imuAcquisitionThread;
    pthread_t ramOperationThread;
    pthread_t bleStackThread;
    pthread_t energySavingThread;
    pthread_t customEventHandlerThread;
    pthread_t fsrAcquisitionThread;

    pthread_create(&imuAcquisitionThread, NULL, IMU_Acquisition_func, NULL);
    pthread_create(&ramOperationThread, NULL, RAM_Operation_func, NULL);
    pthread_create(&bleStackThread, NULL, BLE_Stack_Operation_func, NULL);
    pthread_create(&energySavingThread, NULL, Energy_Saving_func, NULL);
    pthread_create(&customEventHandlerThread, NULL, Custom_Event_Handler_func, NULL);
    pthread_create(&fsrAcquisitionThread, NULL, FSR_Acquisition_func, NULL);

    OrchestratorMain orchestratorMain;
    printf("Me meto en orchestrator.start\n");
    orchestratorMain.start();

    pthread_join(fsrAcquisitionThread, NULL);
    pthread_join(imuAcquisitionThread, NULL);
    pthread_join(ramOperationThread, NULL);
    pthread_join(bleStackThread, NULL);
    pthread_join(energySavingThread, NULL);
    pthread_join(customEventHandlerThread, NULL);

    return 0;
}