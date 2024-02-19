#include <iostream>
#include <pthread.h>
#include "dma_monitor.h"

DMAMonitor dmaMonitor;

void *workerFunction(void *arg)
{
    dmaMonitor.incrementDMA();
    int value = dmaMonitor.getDMA();
    std::cout << "DMA Value: " << value << std::endl;
    return NULL;
}

int main()
{
    const int NUM_THREADS = 10;
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_create(&threads[i], NULL, workerFunction, NULL);
    }

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
