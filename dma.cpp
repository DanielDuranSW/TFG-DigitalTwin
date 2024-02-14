#include "dma.h"
#include <iostream>

using namespace std;

static int dma = 0;
static pthread_mutex_t mutexVariableDMA;

void inicializarDMA()
{
    pthread_mutex_init(&mutexVariableDMA, NULL);
}

void incrementarDMA()
{
    pthread_mutex_lock(&mutexVariableDMA);
    dma += 1;
    pthread_mutex_unlock(&mutexVariableDMA);
}

void imprimirDMA()
{
    pthread_mutex_lock(&mutexVariableDMA);
    cout << "Variable compartida: " << dma << endl;
    pthread_mutex_unlock(&mutexVariableDMA);
}
