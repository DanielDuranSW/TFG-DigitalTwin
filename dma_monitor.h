// dma_monitor.h
#pragma once
#include <pthread.h>

class DMAMonitor
{
private:
    int currentStage;
    pthread_mutex_t mtx;
    pthread_cond_t cv_fsr, cv_imu, cv_ram, cv_ble, cv_energy, cv_custom;

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
};
