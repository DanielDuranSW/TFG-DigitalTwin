// main.cpp
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "ManagerGUI.h"
#include "threads/BLE_Stack_Operation.h"
#include "threads/Custom_Event_Handler.h"
#include "threads/FSR_Acquisition.h"
#include "threads/IMU_Acquisition.h"
#include "threads/RAM_Operation.h"
#include "threads/Energy_Saving.h"
#include "threads/CSVReader.h"
#include "ThreadsData.h"
#include "resources/RTC.h"
#include "config.h"

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
    pthread_t ramToFlashThread;
    pthread_t guiThread;
    pthread_t rtcThread;

    State state;
    StateSignalHandler stateSignalHandler;
    RAM ram(&stateSignalHandler);
    Resource resource;
    CSVReader csvReaderFSR("/home/daniduran/ws/TFG-DigitalTwin/data/data2.csv");
    CSVReader csvReaderIMU("/home/daniduran/ws/TFG-DigitalTwin/data/data2.csv");

    Instances argsInstance;
    argsInstance.state = state;
    argsInstance.ram = RAM(&stateSignalHandler);
    argsInstance.stateSignalHandler = &stateSignalHandler;
    argsInstance.resource = resource;
    argsInstance.csvReaderFSR = &csvReaderFSR;
    argsInstance.csvReaderIMU = &csvReaderIMU;
    argsInstance.dataPacket = DataPacket();

    GUIArguments guiArgs;
    guiArgs.argc = argc;
    guiArgs.argv = argv;
    guiArgs.stateSignalHandler = &stateSignalHandler;

    pthread_create(&guiThread, NULL, gui_run, &guiArgs);
    usleep(INITIAL_WAIT);
    pthread_create(&fsrAcquisitionThread, NULL, fsr_run, &argsInstance.state);
    pthread_create(&imuAcquisitionThread, NULL, imu_run, &argsInstance.state);
    pthread_create(&ramOperationThread, NULL, ram_run, &argsInstance);
    pthread_create(&bleStackThread, NULL, ble_run, &argsInstance.state);
    pthread_create(&energySavingThread, NULL, energy_run, &argsInstance.state);
    pthread_create(&customEventHandlerThread, NULL, custom_run, &argsInstance.state);
    pthread_create(&ramToFlashThread, NULL, ram_checkAndConsume, &argsInstance.ram);
    pthread_create(&rtcThread, NULL, rtc_run, &argsInstance);

    pthread_join(fsrAcquisitionThread, NULL);
    pthread_join(imuAcquisitionThread, NULL);
    pthread_join(ramOperationThread, NULL);
    pthread_join(bleStackThread, NULL);
    pthread_join(energySavingThread, NULL);
    pthread_join(customEventHandlerThread, NULL);
    pthread_join(ramToFlashThread, NULL);
    pthread_join(guiThread, NULL);

    return 0;
}
