#ifndef RAM_OPERATION_H
#define RAM_OPERATION_H

#include "/home/daniduran/ws/TFG-DigitalTwin/State.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/resources/RAM.h"
#include "/home/daniduran/ws/TFG-DigitalTwin/ThreadsData.h"

void *ram_run(void *arg);
void ram_function(RAM *ram);

#endif
