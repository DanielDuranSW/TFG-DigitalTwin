// dma_monitor.cpp
#include "dma_monitor.h"

DMAMonitor::DMAMonitor() : currentStage(0)
{
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&cv_fsr, NULL);
    pthread_cond_init(&cv_imu, NULL);
    pthread_cond_init(&cv_ram, NULL);
    pthread_cond_init(&cv_ble, NULL);
    pthread_cond_init(&cv_energy, NULL);
    pthread_cond_init(&cv_custom, NULL);
}

DMAMonitor::~DMAMonitor()
{
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv_fsr);
    pthread_cond_destroy(&cv_imu);
    pthread_cond_destroy(&cv_ram);
    pthread_cond_destroy(&cv_ble);
    pthread_cond_destroy(&cv_energy);
    pthread_cond_destroy(&cv_custom);
}

void DMAMonitor::incrementStage()
{
    pthread_mutex_lock(&mtx);
    currentStage++;
    switch (currentStage)
    {
    case 1:
        pthread_cond_signal(&cv_fsr);
        break;
    case 2:
        pthread_cond_signal(&cv_imu);
        break;
    case 3:
        pthread_cond_signal(&cv_ram);
        break;
    case 4:
        pthread_cond_signal(&cv_ble);
        break;
    case 5:
        pthread_cond_signal(&cv_energy);
        break;
    case 6:
        pthread_cond_signal(&cv_custom);
        break;
    default:
        std::cout << "Invalid stage" << std::endl;
    }
    pthread_mutex_unlock(&mtx);
}

// Aqui alomejor es mejor hacer un método de incremetar general y orientarlo de otra forma
void DMAMonitor::FSR_Acquisition()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 1)
    {
        pthread_cond_wait(&cv_fsr, &mtx);
    }
    // Lógica
    incrementStage();
    pthread_mutex_unlock(&mtx);
}

void DMAMonitor::IMU_Acquisition()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 2)
    {
        pthread_cond_wait(&cv_fsr, &mtx);
    }
    // Lógica
    incrementStage();
    pthread_mutex_unlock(&mtx);
}

void DMAMonitor::RAM_Operation()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 3)
    {
        pthread_cond_wait(&cv_fsr, &mtx);
    }
    // Lógica
    incrementStage();
    pthread_mutex_unlock(&mtx);
}

void DMAMonitor::BLE_Stack_Operation()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 4)
    {
        pthread_cond_wait(&cv_fsr, &mtx);
    }
    // Lógica
    incrementStage();
    pthread_mutex_unlock(&mtx);
}

void DMAMonitor::Energy_Saving()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 5)
    {
        pthread_cond_wait(&cv_fsr, &mtx);
    }
    // Lógica
    incrementStage();
    pthread_mutex_unlock(&mtx);
}
void DMAMonitor::Custom_Event_Handler()
{
    pthread_mutex_lock(&mtx);
    while (currentStage != 6)
    {
        pthread_cond_wait(&cv_fsr, &mtx);
    }
    // Lógica
    incrementStage();
    pthread_mutex_unlock(&mtx);
}