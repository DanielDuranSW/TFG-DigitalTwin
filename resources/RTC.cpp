// RTC.cpp
#include "RTC.h"
#include <unistd.h>

void *rtc_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    Resource *resource = &(args->resource);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;

    while (true)
    {
        // Esperar a que le notifique el hilo energy saving
        // Hacer un sleep
        // Despertar al hilo energy saving

        resource->lockMutex();
        resource->waitCondition();
        usleep(RESOURCE_RTC_DURATION);
        stateSignalHandler->onWorking("Rtc", true);
        resource->signalCondition();
        resource->unlockMutex();
    }
    pthread_exit(NULL);
}
