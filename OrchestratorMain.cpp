// OrchestratorMain.cpp
#include "OrchestratorMain.h"

OrchestratorMain::OrchestratorMain()
{
    // state = new State();
}

OrchestratorMain::~OrchestratorMain()
{
    // delete state;
}

static void *fsr_acquisition_func(void *arg)
{
    FSR_Acquisition *fsrAcquisition = (FSR_Acquisition *)arg;
    fsrAcquisition->run();
    return NULL;
}

static void *imu_acquisition_func(void *arg)
{
    IMU_Acquisition *imuAcquisition = (IMU_Acquisition *)arg;
    imuAcquisition->run();
    return NULL;
}

static void *ram_operation_func(void *arg)
{
    RAM_Operation *ramOperation = (RAM_Operation *)arg;
    ramOperation->run();
    return NULL;
}

static void *ble_stack_operation_func(void *arg)
{
    BLE_Stack_Operation *bleStack = (BLE_Stack_Operation *)arg;
    bleStack->run();
    return NULL;
}

static void *energy_saving_func(void *arg)
{
    Energy_Saving *energySaving = (Energy_Saving *)arg;
    energySaving->run();
    return NULL;
}

static void *custom_event_handler_func(void *arg)
{
    Custom_Event_Handler *customEventHandler = (Custom_Event_Handler *)arg;
    customEventHandler->run();
    return NULL;
}

void OrchestratorMain::start()
{
    int maxStages = 6;
    int currentStage = 0;

    // // Monitores
    // FSR_Acquisition *fsrAcquisition = new FSR_Acquisition(state->getCV_FSR(), state->getMutex());
    // IMU_Acquisition *imuAcquisition = new IMU_Acquisition(state->getCV_IMU(), state->getMutex());
    // RAM_Operation *ramOperation = new RAM_Operation(state->getCV_RAM(), state->getMutex());
    // BLE_Stack_Operation *bleStack = new BLE_Stack_Operation(state->getCV_BLE(), state->getMutex());
    // Energy_Saving *energySaving = new Energy_Saving(state->getCV_ENERGY(), state->getMutex());
    // Custom_Event_Handler *customEventHandler = new Custom_Event_Handler(state->getCV_CUSTOM(), state->getMutex());

    pthread_mutex_t mtx_threads;
    pthread_cond_t cv_fsr, cv_imu, cv_ram, cv_ble, cv_energy, cv_custom;

    pthread_mutex_init(&mtx_threads, NULL);
    pthread_cond_init(&cv_fsr, NULL);
    pthread_cond_init(&cv_imu, NULL);
    pthread_cond_init(&cv_ram, NULL);
    pthread_cond_init(&cv_ble, NULL);
    pthread_cond_init(&cv_energy, NULL);
    pthread_cond_init(&cv_custom, NULL);

    // Monitores
    FSR_Acquisition *fsrAcquisition = new FSR_Acquisition(&cv_fsr, &mtx_threads);
    IMU_Acquisition *imuAcquisition = new IMU_Acquisition(&cv_imu, &mtx_threads);
    RAM_Operation *ramOperation = new RAM_Operation(&cv_ram, &mtx_threads);
    BLE_Stack_Operation *bleStack = new BLE_Stack_Operation(&cv_ble, &mtx_threads);
    Energy_Saving *energySaving = new Energy_Saving(&cv_energy, &mtx_threads);
    Custom_Event_Handler *customEventHandler = new Custom_Event_Handler(&cv_custom, &mtx_threads);

    pthread_t imuAcquisitionThread;
    pthread_t ramOperationThread;
    pthread_t bleStackThread;
    pthread_t energySavingThread;
    pthread_t customEventHandlerThread;
    pthread_t fsrAcquisitionThread;

    pthread_create(&fsrAcquisitionThread, NULL, fsr_acquisition_func, fsrAcquisition);
    pthread_create(&imuAcquisitionThread, NULL, imu_acquisition_func, imuAcquisition);
    pthread_create(&ramOperationThread, NULL, ram_operation_func, ramOperation);
    pthread_create(&bleStackThread, NULL, ble_stack_operation_func, bleStack);
    pthread_create(&energySavingThread, NULL, energy_saving_func, energySaving);
    pthread_create(&customEventHandlerThread, NULL, custom_event_handler_func, customEventHandler);

    // Esperamos a que todos los hilos estén listos
    sleep(3);

    printf("Todos los hilos listos. Empezamos OrchestratorMain\n");

    // pthread_mutex_lock(state->getMutex());
    while (currentStage < maxStages)
    {
        switch (currentStage)
        {
        case 0:
            sleep(1);
            printf("Te doy signal FSR con currentState= %d\n", currentStage);
            pthread_cond_signal(&cv_fsr);
            currentStage++;
            printf("FSR da paso al siguiente con currentState= %d\n", currentStage);
            break;

        case 1:
            sleep(1);
            printf("Te doy signal IMU con currentState= %d\n", currentStage);
            pthread_cond_signal(&cv_imu);
            currentStage++;
            printf("IMU da paso al siguiente con currentState= %d\n", currentStage);
            break;

        case 2:
            sleep(1);
            printf("Te doy signal RAM con currentState= %d\n", currentStage);
            pthread_cond_signal(&cv_ram);
            currentStage++;
            printf("RAM da paso al siguiente con currentState= %d\n", currentStage);
            break;

        case 3:
            sleep(1);
            printf("Te doy signal BLE con currentState= %d\n", currentStage);
            pthread_cond_signal(&cv_ble);
            currentStage++;
            printf("BLE da paso al siguiente con currentState= %d\n", currentStage);
            break;

        case 4:
            sleep(1);
            printf("Te doy signal ENERGY con currentState= %d\n", currentStage);
            pthread_cond_signal(&cv_energy);
            currentStage++;
            printf("ENERGY da paso al siguiente con currentState= %d\n", currentStage);
            break;

        case 5:
            sleep(1);
            printf("Te doy signal CUSTOM con currentState= %d\n", currentStage);
            pthread_cond_signal(&cv_custom);
            currentStage = 0;
            printf("CUSTOM da paso al siguiente con currentState= %d\n", currentStage);
            break;
        }
    }
    // pthread_mutex_unlock(state->getMutex());

    pthread_join(fsrAcquisitionThread, NULL);
    pthread_join(imuAcquisitionThread, NULL);
    pthread_join(ramOperationThread, NULL);
    pthread_join(bleStackThread, NULL);
    pthread_join(energySavingThread, NULL);
    pthread_join(customEventHandlerThread, NULL);
}