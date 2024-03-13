// RAM_Operation.cpp
#include "RAM_Operation.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

extern pthread_mutex_t mutex;
extern pthread_cond_t cond;
extern int current_stage;

void *ram_function(void *arg)
{
    pthread_mutex_lock(&mutex);
    while (current_stage != 2)
    {
        pthread_cond_wait(&cond, &mutex);
    }

    printf("RAM ejecutando...\n");
    sleep(1); // Simulación de trabajo
    printf("RAM terminado\n");

    current_stage++;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}
