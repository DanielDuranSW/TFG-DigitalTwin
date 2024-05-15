// ThreadsData.h
#ifndef THREADS_DATA_H
#define THREADS_DATA_H

#include "resources/RAM.h"
#include "State.h"
#include "StateSignalHandler.h"
#include "resources/Resource.h"
#include "resources/CSVReader.h"
#include "DataPacket.h"
#include "resources/ClassifierFeatures.h"

struct Instances
{
    State state;
    RAM ram;
    StateSignalHandler *stateSignalHandler;
    Resource resource;
    CSVReader *csvReaderFSR;
    CSVReader *csvReaderIMU;
    DataPacket dataPacket;
    std::vector<int> fsrData;
    std::vector<int> imuData;
    std::vector<uint8_t> leftoverData;
    ClassifierFeatures *classifierFeatures;

    Instances() : ram(nullptr) {}
};

#endif // THREADS_DATA_H
