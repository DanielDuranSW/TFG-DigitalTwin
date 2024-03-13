// State.cpp
#include "State.h"

State::State()
{
    pthread_mutex_init(&mtx_threads, NULL);
    pthread_cond_init(&cv_fsr, NULL);
    pthread_cond_init(&cv_imu, NULL);
    pthread_cond_init(&cv_ram, NULL);
    pthread_cond_init(&cv_ble, NULL);
    pthread_cond_init(&cv_energy, NULL);
    pthread_cond_init(&cv_custom, NULL);

    pthread_mutex_init(&startMutex, NULL);
    pthread_cond_init(&startCond, NULL);
}

State::~State()
{
    pthread_mutex_destroy(&mtx_threads);
    pthread_cond_destroy(&cv_fsr);
    pthread_cond_destroy(&cv_imu);
    pthread_cond_destroy(&cv_ram);
    pthread_cond_destroy(&cv_ble);
    pthread_cond_destroy(&cv_energy);
    pthread_cond_destroy(&cv_custom);

    pthread_mutex_destroy(&startMutex);
    pthread_cond_destroy(&startCond);
}

// State *State::instance = nullptr;

// State *State::getInstance()
// {
//     if (!instance)
//     {
//         instance = new State();
//     }
//     return instance;
// }

void State::nextStage()
{
    currentStage++;
}

void State::resetStage()
{
    currentStage = 0;
}
