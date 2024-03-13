// IMU_Acquisition.cpp
#include "IMU_Acquisition.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

extern pthread_mutex_t mutex;
extern pthread_cond_t cond;
extern int current_stage;

void *imu_function(void *arg)
{
    pthread_mutex_lock(&mutex);
    while (current_stage != 1)
    {
        pthread_cond_wait(&cond, &mutex);
    }

    printf("IMU ejecutando...\n");
    sleep(1); // Simulación de trabajo
    printf("IMU terminado\n");

    current_stage++;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}
