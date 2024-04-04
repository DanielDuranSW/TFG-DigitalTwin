// main.cpp
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "ManagerGUI.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/threads/BLE_Stack_Operation.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/threads/Custom_Event_Handler.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/threads/FSR_Acquisition.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/threads/IMU_Acquisition.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/threads/RAM_Operation.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/threads/Energy_Saving.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/ThreadsData.h"

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    pthread_t fsrAcquisitionThread;
    pthread_t imuAcquisitionThread;
    pthread_t ramOperationThread;
    pthread_t bleStackThread;
    pthread_t energySavingThread;
    pthread_t customEventHandlerThread;
    pthread_t ramToFlashThread1;
    pthread_t ramToFlashThread2;
    pthread_t guiThread;

    State state;
    RAM ram;

    Instances argsInstance;
    argsInstance.state = state;
    argsInstance.ram = ram;

    GUIArguments guiArgs;
    guiArgs.argc = argc;
    guiArgs.argv = argv;

    pthread_create(&fsrAcquisitionThread, NULL, fsr_run, &argsInstance.state);
    pthread_create(&imuAcquisitionThread, NULL, imu_run, &argsInstance.state);
    pthread_create(&ramOperationThread, NULL, ram_run, &argsInstance);
    pthread_create(&bleStackThread, NULL, ble_run, &argsInstance.state);
    pthread_create(&energySavingThread, NULL, energy_run, &argsInstance.state);
    pthread_create(&customEventHandlerThread, NULL, custom_run, &argsInstance.state);
    pthread_create(&ramToFlashThread1, NULL, ram_checkAndConsume, &argsInstance.ram);
    pthread_create(&ramToFlashThread2, NULL, ram_checkAndConsume, &argsInstance.ram);
    pthread_create(&guiThread, NULL, gui_run, &guiArgs);

    pthread_join(fsrAcquisitionThread, NULL);
    pthread_join(imuAcquisitionThread, NULL);
    pthread_join(ramOperationThread, NULL);
    pthread_join(bleStackThread, NULL);
    pthread_join(energySavingThread, NULL);
    pthread_join(customEventHandlerThread, NULL);
    pthread_join(ramToFlashThread1, NULL);
    pthread_join(ramToFlashThread2, NULL);
    pthread_join(guiThread, NULL);

    return 0;
}
