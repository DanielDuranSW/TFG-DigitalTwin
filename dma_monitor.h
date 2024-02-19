#pragma once
#include <pthread.h>
#include <cstring>
#include <iostream>

class DMAMonitor
{
private:
    int currentStage;
    static int sharedCounter;
    pthread_mutex_t mtx;
    pthread_cond_t cv_fsr, cv_imu, cv_ram, cv_ble, cv_energy, cv_custom;
    static pthread_mutex_t mtx_sharedCounter;

public:
    DMAMonitor();
    ~DMAMonitor();
    void incrementStage();
    void FSR_Acquisition();
    void IMU_Acquisition();
    void RAM_Operation();
    void BLE_Stack_Operation();
    void Energy_Saving();
    void Custom_Event_Handler();
    // static void incrementSharedCounter();
    void incrementSharedCounter(const std::string &caller);
};
