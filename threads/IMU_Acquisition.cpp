// IMU_Acquisition.cpp
#include "IMU_Acquisition.h"

void *imu_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;

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
        printf("IMU terminado\n");
        stateSignalHandler->onWorking("Imu", false);

        state->setCurrentStage(2);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
