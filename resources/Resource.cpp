// Resource.cpp
#include "Resource.h"

Resource::Resource() {}

Resource::~Resource() {}
// ¿como accedo al mutex desde 2 archivos distintos?
void Resource::add(int item)
{
    pthread_mutex_lock(&mutex);

    while (count == capacity)
    { // Buffer lleno
        pthread_cond_wait(&can_produce, &mutex);
    }

    buffer[writePos] = item;
    writePos = (writePos + 1) % capacity;
    ++count;

    pthread_cond_signal(&can_consume);
    pthread_mutex_unlock(&mutex);
}

int Resource::remove()
{
    pthread_mutex_lock(&mutex);

    while (count == 0)
    { // Buffer vacío
        pthread_cond_wait(&can_consume, &mutex);
    }

    int item = buffer[readPos];
    readPos = (readPos + 1) % capacity;
    --count;

    pthread_cond_signal(&can_produce);
    pthread_mutex_unlock(&mutex);

    return item;
}