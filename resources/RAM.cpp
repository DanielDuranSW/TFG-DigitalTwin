// RAM.cpp
#include "RAM.h"

pthread_mutex_t shared_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t can_produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_consume = PTHREAD_COND_INITIALIZER;

RAM::RAM(StateSignalHandler *stateSignalHandler)
{
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&can_produce, nullptr);
    pthread_cond_init(&can_consume, nullptr);

    this->stateSignalHandler = stateSignalHandler;
}

RAM::~RAM()
{
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&can_produce);
    pthread_cond_destroy(&can_consume);
}

void *ram_checkAndConsume(void *ram)
{
    RAM *ramInstance = static_cast<RAM *>(ram);
    ramInstance->checkAndConsume();
    // ramInstance->test();
    return NULL;
}

void RAM::test()
{
    std::cout << "Hola cara de cola" << std::endl;
}

void RAM::add(int item)
{
    pthread_mutex_lock(&mutex);

    // Esperar si el buffer está lleno (dejando espacio para anticipar el consumo)(solo por seguridad)
    while (count >= BUFFER_SIZE - 1)
    {
        pthread_cond_wait(&can_produce, &mutex);
    }

    printf("Añadido a buffer con tamaño %d\n", count);
    stateSignalHandler->onWorking("WaitingTransfer",true);
    buffer[writePos] = item;
    writePos = (writePos + 1) % capacity; // Incremento de manera circular
    ++count;

    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&can_consume); // Notificar que hay al menos un elemento para consumir

}

int RAM::remove()
{
    pthread_mutex_lock(&mutex);

    while (count == 0) // Esperar si el buffer está vacío
    {
        pthread_cond_wait(&can_consume, &mutex);
    }

    int item = buffer[readPos];
    readPos = (readPos + 1) % capacity;
    --count;

    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&can_produce); // Notificar que hay espacio para producir

    return item;
}

void RAM::checkAndConsume()
{
    while (true) // Este bucle podría ser controlado por una variable de estado para detenerlo
    {

        printf("Esperando a consumir...con tamaño %d\n", count);
        //pthread_mutex_lock(&mutex);

        // Lógica para anticipar el consumo si el buffer está por llenarse
        if (count >= BUFFER_SIZE - 1)
        {

            // Consumir todos los elementos excepto uno (al que apunta el productor)
            while (count > 1)
            {
                stateSignalHandler->onWorking("RamToFlash",true);
                stateSignalHandler->onWorking("WaitingTransfer",false);
                int consumedItem = buffer[readPos];
                readPos = (readPos + 1) % capacity;
                --count;
                // Procesado del item consumido
                std::cout << "Consumido: " << consumedItem << std::endl;

                sleep(1);
                stateSignalHandler->onWorking("WaitingTransfer",true);
                stateSignalHandler->onWorking("RamToFlash",false);
                sleep(1);

            }
            pthread_cond_signal(&can_produce); // Notificar que hay espacio para producir
        }

        //pthread_mutex_unlock(&mutex);
        sleep(5); // Evitar la sobrecarga
    }
}
