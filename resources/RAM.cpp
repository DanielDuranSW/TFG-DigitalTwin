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

void RAM::add(std::vector<uint8_t> packet)
{
    pthread_mutex_lock(&mutex);

    // Esperar si el buffer está lleno (dejando espacio para anticipar el consumo)(solo por seguridad)
    while (count >= BUFFER_SIZE - 1)
    {
        pthread_cond_wait(&can_produce, &mutex);
    }

    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAA-Contenido del packete es:" << std::endl;
    for (const auto &byte : packet)
    {
        std::cout << std::hex << static_cast<int>(byte) << " "; // Imprimir el byte en hexadecimal
    }
    std::cout << std::endl;

    QString bufferName = QString("Buffer%1").arg(writePos);
    printf("----------------------Dibujo nombre del buffer: %s\n", qPrintable(bufferName));
    stateSignalHandler->onWorkingBuffer(bufferName, true); // aqui se deberia dibujar el rectangulo
    printf("Añadido a buffer con tamaño %d\n", count);
    stateSignalHandler->onWorking("WaitingTransfer", true);
    buffer[writePos] = packet;
    // buffer[writePos] = 1;
    writePos = (writePos + 1) % capacity; // Incremento de manera circular
    ++count;

    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&can_consume); // Notificar que hay al menos un elemento para consumir
}

/*int RAM::remove()
{
    pthread_mutex_lock(&mutex);

    while (count == 0) // Esperar si el buffer está vacío
    {
        pthread_cond_wait(&can_consume, &mutex);
    }

    int packet = buffer[readPos];
    readPos = (readPos + 1) % capacity;
    --count;

    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&can_produce); // Notificar que hay espacio para producir

    return packet;
}*/

void RAM::checkAndConsume()
{
    while (true) // Este bucle podría ser controlado por una variable de estado para detenerlo
    {

        // printf("Esperando a consumir...con tamaño %d\n", count);
        // pthread_mutex_lock(&mutex);

        // Lógica para anticipar el consumo si el buffer está por llenarse
        if (count >= BUFFER_SIZE - 1)
        {

            QString FlashName = QString("Flash%1").arg(flashCount);
            printf("----------------------Dibujo nombre del Flash: %s\n", qPrintable(FlashName));
            stateSignalHandler->onWorkingBuffer(FlashName, true);
            ++flashCount;

            // Consumir todos los elementos excepto uno (al que apunta el productor)
            while (count > 1)
            {
                stateSignalHandler->onWorking("RamToFlash", true);
                stateSignalHandler->onWorking("WaitingTransfer", false);

                QString bufferName = QString("Buffer%1").arg(readPos);
                printf("----------------------Borro nombre del buffer: %s\n", qPrintable(bufferName));
                stateSignalHandler->onWorkingBuffer(bufferName, false);

                std::vector<uint8_t> consumedPacket = buffer[readPos];
                flashMemory.push_back(consumedPacket);
                readPos = (readPos + 1) % capacity;
                --count;

                // Procesado del packet consumido
                // std::cout << "Consumido: " << consumedpacket << std::endl;

                usleep(STATE_GENERAL_DURATION);
                stateSignalHandler->onWorking("WaitingTransfer", true);
                stateSignalHandler->onWorking("RamToFlash", false);
                usleep(STATE_GENERAL_DURATION);
            }
            pthread_cond_signal(&can_produce); // Notificar que hay espacio para producir
        }

        // pthread_mutex_unlock(&mutex);
        usleep(RAM_BUFFER_RATIO_REFRESH); // Evitar la sobrecarga
    }
}
