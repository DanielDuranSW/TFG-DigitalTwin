// FSR_Acquisition.cpp
#include "FSR_Acquisition.h"

void *fsr_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;
    CSVReader *csvReaderFSR = args->csvReaderFSR;

    while (!terminateFlag)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 0)
        {
            state->waitCondition();
        }
        stateSignalHandler->onWorking("Fsr", true);
        // printf("FSR_Acquisition ejecutando...\n");

        if (realSimulation)
        {
            usleep(STATE_FSR_DURATION);
        }
        else
        {
            usleep(STATE_GENERAL_DURATION);
        }

        std::vector<int> fsrData;
        csvReaderFSR->getcsvFSR(fsrData);
        args->fsrData = fsrData;

        INTENSITY_CONSUMED += STATE_GENERAL_INTENSITY;
        stateSignalHandler->intensityToChange(INTENSITY_CONSUMED);

        // printf("FSR_Acquisition terminado\n");
        stateSignalHandler->onWorking("Fsr", false);

        state->setCurrentStage(1);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
