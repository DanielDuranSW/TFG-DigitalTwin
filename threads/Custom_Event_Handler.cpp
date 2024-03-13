// Custom_Event_Handler.cpp
#include "Custom_Event_Handler.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

extern pthread_mutex_t mutex;
extern pthread_cond_t cond;
extern int current_stage;

void *custom_function(void *arg)
{
    while (true)
    {
        pthread_mutex_lock(&mutex);
        while (current_stage != 5)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("Custom ejecutando...\n");
        sleep(1); // Simulación de trabajo
        printf("Custom terminado\n");

        current_stage = 0;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
