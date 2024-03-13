// OrchestratorMain.cpp

#include "OrchestratorMain.h"

OrchestratorMain::OrchestratorMain() {}

OrchestratorMain::~OrchestratorMain() {}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int current_stage = 0;

void OrchestratorMain::start()
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
}
