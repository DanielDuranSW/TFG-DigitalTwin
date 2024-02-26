// State.cpp
#include "State.h"

int State::currentStage = 0;

State::State()
{
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&cv_fsr, NULL);
    pthread_cond_init(&cv_imu, NULL);
    pthread_cond_init(&cv_ram, NULL);
    pthread_cond_init(&cv_ble, NULL);
    pthread_cond_init(&cv_energy, NULL);
    pthread_cond_init(&cv_custom, NULL);
}

State::~State()
{
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv_fsr);
    pthread_cond_destroy(&cv_imu);
    pthread_cond_destroy(&cv_ram);
    pthread_cond_destroy(&cv_ble);
    pthread_cond_destroy(&cv_energy);
    pthread_cond_destroy(&cv_custom);
}

void State::nextStage()
{
    currentStage++;
}