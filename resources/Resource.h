// Resource.h
#ifndef RESOURCE_H
#define RESOURCE_H

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include "config.h"

// #define BUFFER_SIZE 10
// #define TLB_SIZE 4

class Resource
{
private:
public:
    Resource();
    virtual ~Resource();
};

#endif
