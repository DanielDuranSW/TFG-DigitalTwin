// State.cpp
#include "State.h"

int State::currentStage = 0;
int State::readyCount = 0;
int State::totalThreads = 6;

pthread_mutex_t State::mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t State::cv_fsr = PTHREAD_COND_INITIALIZER;
pthread_cond_t State::cv_imu = PTHREAD_COND_INITIALIZER;
pthread_cond_t State::cv_ram = PTHREAD_COND_INITIALIZER;
pthread_cond_t State::cv_ble = PTHREAD_COND_INITIALIZER;
pthread_cond_t State::cv_energy = PTHREAD_COND_INITIALIZER;
pthread_cond_t State::cv_custom = PTHREAD_COND_INITIALIZER;

pthread_mutex_t State::startMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t State::startCond = PTHREAD_COND_INITIALIZER;

State::State() {}

State::~State() {}

void State::nextStage()
{
    currentStage++;
}

void State::resetStage()
{
    currentStage = 0;
}