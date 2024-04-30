// ThreadsData.h
#ifndef THREADS_DATA_H
#define THREADS_DATA_H

#include "resources/RAM.h"
#include "State.h"
#include "StateSignalHandler.h"
#include "resources/Resource.h"
#include "threads/CSVReader.h"
#include "DataPacket.h"

struct Instances
{
    State state;
    RAM ram;
    StateSignalHandler *stateSignalHandler;
    Resource resource;
    CSVReader *csvReader;
    DataPacket dataPacket;
    std::vector<int> fsrData;
    std::vector<int> imuData;
    std::vector<uint8_t> leftoverData;

    Instances() : ram(nullptr) {}
};

#endif // THREADS_DATA_H
