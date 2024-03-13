// IMU_Acquisition.cpp
#include "IMU_Acquisition.h"

void *imu_run(void *arg)
{
    State *state = static_cast<State *>(arg);
    while (true)
    {
        state->lockMutex();
        while (state->getCurrentStage() != 1)
        {
            state->waitCondition();
        }

        printf("IMU ejecutando...\n");
        sleep(1); // Simulación de trabajo
        printf("IMU terminado\n");

        state->setCurrentStage(2);
        state->broadcastCondition();
        state->unlockMutex();
    }
    pthread_exit(NULL);
}
