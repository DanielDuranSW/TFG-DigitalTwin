// State.cpp
#include "State.h"

State::State() : current_stage(0)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_cond_init(&condLLAC, NULL);
}

State::~State()
{
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    pthread_cond_destroy(&condLLAC);
}

void State::lockMutex()
{
    pthread_mutex_lock(&mutex);
}

void State::unlockMutex()
{
    pthread_mutex_unlock(&mutex);
}

void State::waitCondition()
{
    pthread_cond_wait(&cond, &mutex);
}

void State::signalCondition()
{
    pthread_cond_signal(&cond);
}

void State::broadcastCondition()
{
    pthread_cond_broadcast(&cond);
}

int State::getCurrentStage()
{
    return current_stage;
}

void State::setCurrentStage(int stage)
{
    current_stage = stage;
}

// For LowLevelActivityClassifier

void State::waitConditionLLAC()
{
    pthread_cond_wait(&condLLAC, &mutex);
}

void State::signalConditionLLAC()
{
    pthread_cond_signal(&condLLAC);
}