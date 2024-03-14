// RAM.h

#ifndef RAM_H
#define RAM_H

#include "Resource.h"
#define TLB 4
#define PCK 2
#define BUFFER_SIZE 10

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

public:
    RAM();
    virtual ~RAM();

    void add(int value);
    int remove();
    void checkAndConsume();
    void test();
};

#endif
