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

static void *FSR_Acquisition_func(void *arg)
{
    FSR_Acquisition *fsrAcquisition = (FSR_Acquisition *)arg;
    fsrAcquisition->run();

    delete fsrAcquisition;
    return (void *)true;
}

static void *IMU_Acquisition_func(void *arg)
{
    IMU_Acquisition *imuAcquisition = (IMU_Acquisition *)arg;
    imuAcquisition->run();

    delete imuAcquisition;
    return (void *)true;
}

static void *RAM_Operation_func(void *arg)
{
    RAM_Operation *ramOperation = (RAM_Operation *)arg;
    ramOperation->run();

    delete ramOperation;
    return (void *)true;
}

static void *BLE_Stack_Operation_func(void *arg)
{
    BLE_Stack_Operation *bleStackOperation = (BLE_Stack_Operation *)arg;
    bleStackOperation->run();

    delete bleStackOperation;
    return (void *)true;
}

static void *Energy_Saving_func(void *arg)
{
    Energy_Saving *energySaving = (Energy_Saving *)arg;
    energySaving->run();

    delete energySaving;
    return (void *)true;
}

static void *Custom_Event_Handler_func(void *arg)
{
    Custom_Event_Handler *customEventHandler = (Custom_Event_Handler *)arg;
    customEventHandler->run();

    delete customEventHandler;
    return (void *)true;
}

int main()
{
    pthread_t bleStackThread;
    pthread_t customEventHandlerThread;
    pthread_t fsrAcquisitionThread;
    pthread_t imuAcquisitionThread;
    pthread_t ramOperationThread;
    pthread_t energySavingThread;

    pthread_create(&bleStackThread, NULL, BLE_Stack_Operation_func, NULL);
    pthread_create(&customEventHandlerThread, NULL, Custom_Event_Handler_func, NULL);
    pthread_create(&fsrAcquisitionThread, NULL, FSR_Acquisition_func, NULL);
    pthread_create(&imuAcquisitionThread, NULL, IMU_Acquisition_func, NULL);
    pthread_create(&ramOperationThread, NULL, RAM_Operation_func, NULL);
    pthread_create(&energySavingThread, NULL, Energy_Saving_func, NULL);

    pthread_join(bleStackThread, NULL);
    pthread_join(customEventHandlerThread, NULL);
    pthread_join(fsrAcquisitionThread, NULL);
    pthread_join(imuAcquisitionThread, NULL);
    pthread_join(ramOperationThread, NULL);
    pthread_join(energySavingThread, NULL);

    return 0;
}