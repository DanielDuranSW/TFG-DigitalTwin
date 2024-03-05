#ifndef RESOURCE_H
#define RESOURCE_H

#include <pthread.h>
#include <iostream>
#include <unistd.h>

#define BUFFER_SIZE 10

class Resource
{
private:
    int buffer[BUFFER_SIZE];
    int capacity = BUFFER_SIZE;
    int count = 0;    // Elementos actuales en el buffer
    int writePos = 0; // Índice para escribir el próximo elemento
    int readPos = 0;  // Índice para leer el próximo elemento
    pthread_mutex_t mutex;
    pthread_cond_t can_produce;
    pthread_cond_t can_consume;

public:
    Resource()
    {
        pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&can_produce, nullptr);
        pthread_cond_init(&can_consume, nullptr);
    }

    ~Resource()
    {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&can_produce);
        pthread_cond_destroy(&can_consume);
    }
    void add(int value) {}
    int remove() {}
};

#endif