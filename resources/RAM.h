// RAM.h

#ifndef RAM_H
#define RAM_H

#include "Resource.h"
#include "StateSignalHandler.h"
#include "config.h"

void *ram_checkAndConsume(void *ram);

class RAM : public Resource
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

    StateSignalHandler *stateSignalHandler;

public:
    RAM(StateSignalHandler *stateSignalHandler);
    virtual ~RAM();

    void add(int value);
    int remove();
    void checkAndConsume();
    void test();
};

#endif
