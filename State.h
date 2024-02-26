#ifndef STATE_H
#define STATE_H

#include <pthread.h>
#include <unistd.h>
#include <iostream>

class State
{
protected:
    pthread_mutex_t mtx;
    pthread_cond_t cv_fsr, cv_imu, cv_ram, cv_ble, cv_energy, cv_custom;

    // Para composicion:
    // Insole insole;

public:
    static int currentStage;
    State();
    virtual ~State();
    virtual void run() = 0;  // Método abstracto que deben implementar todos los estados
    static void nextStage(); // Método para avanzar al siguiente estado
};

#endif
