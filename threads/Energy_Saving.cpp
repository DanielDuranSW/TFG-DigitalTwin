// Energy_Saving.cpp
#include "Energy_Saving.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

extern pthread_mutex_t mutex;
extern pthread_cond_t cond;
extern int current_stage;

void *energy_function(void *arg)
{
    pthread_mutex_lock(&mutex);
    while (current_stage != 4)
    {
        pthread_cond_wait(&cond, &mutex);
    }

    printf("energy ejecutando...\n");
    sleep(1); // Simulación de trabajo
    printf("energy terminado\n");

    current_stage++;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}
