// ThreadsData.h
#ifndef THREADS_DATA_H
#define THREADS_DATA_H

#include "resources/RAM.h"
#include "State.h"
#include "StateSignalHandler.h"
#include "resources/Resource.h"
#include "threads/CSVReader.h"

struct Instances
{
    State state;
    RAM ram;
    StateSignalHandler *stateSignalHandler;
    Resource resource;
    CSVReader *csvReader;
    std::vector<int> fsrData;
    std::vector<int> imuData;

    Instances() : ram(nullptr) {}
};

#endif // THREADS_DATA_H
