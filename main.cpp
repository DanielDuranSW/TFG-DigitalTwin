// main.cpp
#include <iostream>
#include <pthread.h>
#include "dma_monitor.h"
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
    DMAMonitor *dmaMonitor = new DMAMonitor();

    pthread_t threads[6];
    FSR_Acquisition *fsrAcquisition = new FSR_Acquisition(dmaMonitor);
    pthread_create(&threads[0], NULL, FSR_Acquisition_func, (void *)fsrAcquisition);

    IMU_Acquisition *imuAcquisition = new IMU_Acquisition(dmaMonitor);
    pthread_create(&threads[1], NULL, IMU_Acquisition_func, (void *)imuAcquisition);

    RAM_Operation *ramOperation = new RAM_Operation(dmaMonitor);
    pthread_create(&threads[2], NULL, RAM_Operation_func, (void *)ramOperation);

    BLE_Stack_Operation *bleStackOperation = new BLE_Stack_Operation(dmaMonitor);
    pthread_create(&threads[3], NULL, BLE_Stack_Operation_func, (void *)bleStackOperation);

    Energy_Saving *energySaving = new Energy_Saving(dmaMonitor);
    pthread_create(&threads[4], NULL, Energy_Saving_func, (void *)energySaving);

    Custom_Event_Handler *customEventHandler = new Custom_Event_Handler(dmaMonitor);
    pthread_create(&threads[5], NULL, Custom_Event_Handler_func, (void *)customEventHandler);

    // Inicialización de la etapa
    dmaMonitor->incrementStage();

    for (int i = 0; i < 6; i++)
    {
        pthread_join(threads[i], NULL);
    }

    delete dmaMonitor;

    return 0;
}
