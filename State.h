// State.h
#ifndef STATE_H
#define STATE_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "config.h"

class State
{
protected:
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int current_stage;

    pthread_cond_t condLLAC;

public:
    State();
    virtual ~State();
    void lockMutex();
    void unlockMutex();
    void waitCondition();
    void signalCondition();
    void broadcastCondition();
    int getCurrentStage();
    void setCurrentStage(int stage);

    // For LowLevelActivityClassifier
    void waitConditionLLAC();
    void signalConditionLLAC();
};

#endif