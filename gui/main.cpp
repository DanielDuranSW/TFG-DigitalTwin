// main.cpp
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "/home/daniduran/ws/TFG-DigitalTwin/threads/BLE_Stack_Operation.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/threads/Custom_Event_Handler.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/threads/FSR_Acquisition.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/threads/IMU_Acquisition.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/threads/RAM_Operation.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/threads/Energy_Saving.h"

#include "/home/daniduran/ws/TFG-DigitalTwin/ThreadsData.h"

#include "/home/daniduran/ws/TFG-DigitalTwin/StateSignalHandler.h"

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    // Crear los hilos
    pthread_t fsrAcquisitionThread;
    pthread_t imuAcquisitionThread;
    pthread_t ramOperationThread;
    pthread_t bleStackThread;
    pthread_t energySavingThread;
    pthread_t customEventHandlerThread;
    pthread_t ramToFlashThread;

    State state;
    RAM ram;

    Instances argsInstance;
    argsInstance.state = state;
    argsInstance.ram = ram;

    QApplication a(argc, argv);
    MainWindow w;
    StateSignalHandler signalHandler;
    QObject::connect(&signalHandler, SIGNAL(circleStateChanged(bool)), &w, SLOT(onCircleStateChanged(bool)));


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
    w.show();

    return a.exec();
}
