// Resource.h
#ifndef RESOURCE_H
#define RESOURCE_H

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include "config.h"

class Resource
{
protected:
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int current_stage;

public:
    Resource();
    virtual ~Resource();
    void lockMutex();
    void unlockMutex();
    void waitCondition();
    void signalCondition();
    void broadcastCondition();
};

#endif
