#include "OrchestratorDMA.h"

OrchestratorDMA::OrchestratorDMA() {}
OrchestratorDMA::~OrchestratorDMA() {}

/*
espera a que este lleno

cuuando esta lleno
tal
tal

cuando esta vacio vuelve a esperar
*/

void OrchestratorDMA::start()
{
    int maxStages = 6;
    const int totalThreads = 6;

    // pthread_mutex_lock(State::getStartMutex());
    // while (State::readyCount < totalThreads)
    // {
    //     printf("Esperando a que todos los hilos estén listos\n");
    //     pthread_cond_wait(State::getStartCond(), State::getStartMutex()); // Espera hasta que todos los hilos estén listos
    // }
    // pthread_mutex_unlock(State::getStartMutex());

    // mutex wait para que le avise el otro orquestador
    printf("Empezamos OrchestratorDMA\n");

    // pthread_mutex_lock(State::getMutex());

    // switch (State::currentStage)
    switch (0)
    {
    case 0:
        sleep(1);
        printf("Paso 1");
        break;

    case 1:
        sleep(1);
        printf("Paso 2");
        break;
    }

    // pthread_mutex_unlock(State::getMutex());
}