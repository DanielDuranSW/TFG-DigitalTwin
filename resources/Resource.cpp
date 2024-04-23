// Resource.cpp
#include "Resource.h"

Resource::Resource()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

Resource::~Resource()
{
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

void Resource::lockMutex()
{
    pthread_mutex_lock(&mutex);
}

void Resource::unlockMutex()
{
    pthread_mutex_unlock(&mutex);
}

void Resource::waitCondition()
{
    pthread_cond_wait(&cond, &mutex);
}

void Resource::signalCondition()
{
    pthread_cond_signal(&cond);
}

void Resource::broadcastCondition()
{
    pthread_cond_broadcast(&cond);
}