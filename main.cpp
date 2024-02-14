#include <iostream>
#include <pthread.h>
#include "dma.h"
#include "threads/FSR_Acquisition.h"
#include "threads/IMU_Acquisition.h"
#include "threads/RAM_Operation.h"
#include "threads/BLE_Stack_Operation.h"
#include "threads/Energy_Saving.h"
#include "threads/Custom_Event_Handler.h"

#define NUM_HILOS 6

int main()
{
    pthread_t hilos[NUM_HILOS];

    inicializarDMA();

    pthread_create(&hilos[0], NULL, FSR_Acquisition, NULL);
    pthread_create(&hilos[1], NULL, IMU_Acquisition, NULL);
    pthread_create(&hilos[2], NULL, RAM_Operation, NULL);
    pthread_create(&hilos[3], NULL, BLE_Stack_Operation, NULL);
    pthread_create(&hilos[4], NULL, Energy_Saving, NULL);
    pthread_create(&hilos[5], NULL, Custom_Event_Handler, NULL);

    // Esperar a que todos los hilos terminen.
    for (int i = 0; i < NUM_HILOS; i++)
    {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}
