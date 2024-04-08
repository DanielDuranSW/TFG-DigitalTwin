// ThreadsData.h
#ifndef THREADS_DATA_H
#define THREADS_DATA_H

#include "resources/RAM.h"
#include "State.h"
#include "StateSignalHandler.h"

struct Instances
{
    State state;
    RAM ram;
    StateSignalHandler *stateSignalHandler;
};

#endif // THREADS_DATA_H
