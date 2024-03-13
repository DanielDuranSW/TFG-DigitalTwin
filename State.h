// State.h
#ifndef STATE_H
#define STATE_H
#include <pthread.h>
#include <unistd.h>
#include <iostream>

class State
{
protected:
    // static State *instance;
    pthread_mutex_t mtx_threads;
    pthread_cond_t cv_imu, cv_ram, cv_ble, cv_energy, cv_custom;

    pthread_mutex_t startMutex;
    pthread_cond_t startCond;

    int currentStage = 0;
    int readyCount = 0;
    int totalThreads = 6;

public:
    // static State *getInstance();
    State();
    ~State();

    void nextStage();  // Método para avanzar al siguiente estado
    void resetStage(); // Método para reiniciar el estado

    pthread_cond_t *getCV_FSR() { return &cv_fsr; }
    pthread_cond_t *getCV_IMU() { return &cv_imu; }
    pthread_cond_t *getCV_RAM() { return &cv_ram; }
    pthread_cond_t *getCV_BLE() { return &cv_ble; }
    pthread_cond_t *getCV_ENERGY() { return &cv_energy; }
    pthread_cond_t *getCV_CUSTOM() { return &cv_custom; }

    pthread_mutex_t *getMutex() { return &mtx_threads; }
    pthread_mutex_t *getStartMutex() { return &startMutex; }
    pthread_cond_t *getStartCond() { return &startCond; }

    int getCurrentStage() { return currentStage; }
    int getReadyCount() { return readyCount; }
    int getTotalThreads() { return totalThreads; }

    void waitThreadsReady();
    void incrementReadyCount();

    pthread_cond_t cv_fsr;
};

#endif