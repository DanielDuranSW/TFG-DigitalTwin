#ifndef RAM_OPERATION_H
#define RAM_OPERATION_H

#include "State.h"
#include "StateSignalHandler.h"
#include "ThreadsData.h"
#include "resources/RAM.h"

void *ram_run(void *arg);
void ram_function(Instances *args);

#endif
