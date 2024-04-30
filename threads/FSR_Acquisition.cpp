// FSR_Acquisition.cpp
#include "FSR_Acquisition.h"

void *fsr_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;
    CSVReader *csvReader = args->csvReader;

    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 0)
        {
            state->waitCondition();
        }
        stateSignalHandler->onWorking("Rtc", false);
        stateSignalHandler->onWorking("Fsr", true);
        printf("FSR_Acquisition ejecutando...\n");
        usleep(STATE_GENERAL_DURATION); // Simulación de trabajo

        std::vector<int> fsrData;
        std::vector<int> imuData;
        csvReader->getNextLine(fsrData, imuData);
        args->fsrData = fsrData;

        printf("FSR_Acquisition terminado\n");
        stateSignalHandler->onWorking("Fsr", false);

        state->setCurrentStage(1);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
