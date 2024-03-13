#ifndef STATE_H
#define STATE_H
#include <pthread.h>
#include <unistd.h>
#include <iostream>

class State
{
protected:
    static pthread_mutex_t mtx_threads;
    static pthread_cond_t cv_fsr, cv_imu, cv_ram, cv_ble, cv_energy, cv_custom;

    static pthread_mutex_t startMutex;
    static pthread_cond_t startCond;

public:
    static int currentStage;
    static int readyCount;
    static int totalThreads;

    State();
    virtual ~State();
    virtual void run() = 0;   // Método abstracto que deben implementar todos los estados
    static void nextStage();  // Método para avanzar al siguiente estado
    static void resetStage(); // Método para reiniciar el estado

    static pthread_cond_t *getCV_FSR() { return &cv_fsr; }
    static pthread_cond_t *getCV_IMU() { return &cv_imu; }
    static pthread_cond_t *getCV_RAM() { return &cv_ram; }
    static pthread_cond_t *getCV_BLE() { return &cv_ble; }
    static pthread_cond_t *getCV_ENERGY() { return &cv_energy; }
    static pthread_cond_t *getCV_CUSTOM() { return &cv_custom; }

    static pthread_mutex_t *getMutex() { return &mtx_threads; }
    static pthread_mutex_t *getStartMutex() { return &startMutex; }
    static pthread_cond_t *getStartCond() { return &startCond; }
};

#endif