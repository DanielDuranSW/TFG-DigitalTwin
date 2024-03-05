// OrchestratorMain.cpp
#include "OrchestratorMain.h"

OrchestratorMain::OrchestratorMain()
{
    // insole = new Insole(); // Para asociación con Insole
}

OrchestratorMain::~OrchestratorMain()
{
    // delete insole; // Para asociación con Insole
}

void OrchestratorMain::start()
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

    printf("Empezamos OrchestratorMain\n");

    pthread_mutex_lock(State::getMutex());
    while (State::currentStage < maxStages)
    {
        switch (State::currentStage)
        {
        case 0:
            sleep(1);
            printf("Te doy signal FSR con currentState= %d\n", State::currentStage);
            pthread_cond_signal(State::getCV_FSR());
            State::nextStage();
            printf("FSR da paso al siguiente con currentState= %d\n", State::currentStage);
            break;

        case 1:
            sleep(1);
            printf("Te doy signal IMU con currentState= %d\n", State::currentStage);
            pthread_cond_signal(State::getCV_IMU());
            State::nextStage();
            printf("IMU da paso al siguiente con currentState= %d\n", State::currentStage);
            break;

        case 2:
            sleep(1);
            printf("Te doy signal RAM con currentState= %d\n", State::currentStage);
            pthread_cond_signal(State::getCV_RAM());
            State::nextStage();
            printf("RAM da paso al siguiente con currentState= %d\n", State::currentStage);
            break;

        case 3:
            sleep(1);
            printf("Te doy signal BLE con currentState= %d\n", State::currentStage);
            pthread_cond_signal(State::getCV_BLE());
            State::nextStage();
            printf("BLE da paso al siguiente con currentState= %d\n", State::currentStage);
            break;

        case 4:

            sleep(1);
            printf("Te doy signal ENERGY con currentState= %d\n", State::currentStage);
            pthread_cond_signal(State::getCV_ENERGY());
            State::nextStage();
            printf("ENERGY da paso al siguiente con currentState= %d\n", State::currentStage);
            break;

        case 5:

            sleep(1);
            printf("Te doy signal CUSTOM con currentState= %d\n", State::currentStage);
            pthread_cond_signal(State::getCV_CUSTOM());
            State::resetStage();
            printf("CUSTOM da paso al siguiente con currentState= %d\n", State::currentStage);
            break;
        }
    }
    pthread_mutex_unlock(State::getMutex());
}