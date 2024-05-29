// IMU_Acquisition.cpp
#include "IMU_Acquisition.h"

void *imu_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;
    CSVReader *csvReaderIMU = args->csvReaderIMU;

    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 1)
        {
            state->waitCondition();
        }

        stateSignalHandler->onWorking("Imu", true);
        printf("IMU ejecutando...\n");
        usleep(STATE_GENERAL_DURATION); // Simulación de trabajo

        std::vector<int> imuData;
        csvReaderIMU->getcsvIMU(imuData);
        args->imuData = imuData;

        INTENSITY_CONSUMED += 0.1;
        stateSignalHandler->intensityToChange(INTENSITY_CONSUMED);

        printf("IMU terminado\n");
        stateSignalHandler->onWorking("Imu", false);

        // Dar paso a LLAC
        state->signalConditionLLAC();

        state->setCurrentStage(2);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
