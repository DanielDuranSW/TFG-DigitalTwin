// OrchestratorMain.cpp

#include "OrchestratorMain.h"

OrchestratorMain::OrchestratorMain() {}

OrchestratorMain::~OrchestratorMain() {}

void OrchestratorMain::start()
{
    State state;

    pthread_t fsrAcquisitionThread;
    pthread_t imuAcquisitionThread;
    pthread_t ramOperationThread;
    pthread_t bleStackThread;
    pthread_t energySavingThread;
    pthread_t customEventHandlerThread;

    // Crear los hilos
    pthread_create(&fsrAcquisitionThread, NULL, fsr_run, &state);
    pthread_create(&imuAcquisitionThread, NULL, imu_run, &state);
    pthread_create(&ramOperationThread, NULL, ram_run, &state);
    pthread_create(&bleStackThread, NULL, ble_run, &state);
    pthread_create(&energySavingThread, NULL, energy_run, &state);
    pthread_create(&customEventHandlerThread, NULL, custom_run, &state);

    // Esperar a que todos los hilos terminen
    pthread_join(fsrAcquisitionThread, NULL);
    pthread_join(imuAcquisitionThread, NULL);
    pthread_join(ramOperationThread, NULL);
    pthread_join(bleStackThread, NULL);
    pthread_join(energySavingThread, NULL);
    pthread_join(customEventHandlerThread, NULL);
}
