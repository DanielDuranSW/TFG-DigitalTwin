// RAM_Operation.cpp
#include "RAM_Operation.h"
#include "DataPacket.h"

void *ram_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    StateSignalHandler *stateSignalHandler = args->stateSignalHandler;

    while (!terminateFlag)
    {
        args->state.lockMutex();
        while (args->state.getCurrentStage() != 2)
        {
            args->state.waitCondition();
        }
        stateSignalHandler->onWorking("Ram", true);
        // printf("RAM_Operation ejecutando...\n");
        ram_function(args);

        INTENSITY_CONSUMED += 0.1;
        stateSignalHandler->intensityToChange(INTENSITY_CONSUMED);

        // printf("RAM_Operation terminado\n");
        stateSignalHandler->onWorking("Ram", false);
        args->state.setCurrentStage(3);
        args->state.broadcastCondition();
        args->state.unlockMutex();
    }
    pthread_exit(NULL);
}

void ram_function(Instances *args)
{
    std::vector<int> fsrData = args->fsrData;
    std::vector<int> imuData = args->imuData;
    // printf("FSR Data: \n");
    // printVector(fsrData);
    // printf("IMU Data: \n");
    // printVector(imuData);

    // Convertir los datos de fsr e imu a bytes
    std::vector<uint8_t> fsrBytes;
    for (const auto &value : fsrData)
    {
        uint8_t byte1 = (value >> 8) & 0xFF; // Obtener el byte más significativo
        uint8_t byte2 = value & 0xFF;        // Obtener el byte menos significativo
        fsrBytes.push_back(byte1);
        fsrBytes.push_back(byte2);
    }

    std::vector<uint8_t> imuBytes;
    for (const auto &value : imuData)
    {
        uint8_t byte1 = (value >> 8) & 0xFF; // Obtener el byte más significativo
        uint8_t byte2 = value & 0xFF;        // Obtener el byte menos significativo
        imuBytes.push_back(byte1);
        imuBytes.push_back(byte2);
    }

    // Combinar los bytes de fsr e imu en una sola variable 76 bytes
    std::vector<uint8_t> data;
    data.reserve(fsrBytes.size() + imuBytes.size());
    data.insert(data.end(), fsrBytes.begin(), fsrBytes.end());
    data.insert(data.end(), imuBytes.begin(), imuBytes.end());

    // std::cout << "Contenido del vector data:" << std::endl;
    // for (const auto &byte : data)
    // {
    //     std::cout << std::hex << static_cast<int>(byte) << " "; // Imprimir el byte en hexadecimal
    // }
    // std::cout << std::endl;

    // Recuperar DataPacket y añadir los bytes
    DataPacket &dataPacket = args->dataPacket;
    size_t bytesLeft = dataPacket.getBytesLeft();
    // printf("EEEEEEEEEEE-Bytes left: %ld\n", bytesLeft);
    // printf("OOOOOOOOOOO-Data size: %ld\n", data.size());

    // Si los datos caben en el paquete, añadirlos
    if (bytesLeft >= data.size())
    {
        dataPacket.insert_data(data);
    }
    else
    {
        // Si los datos no caben, añadir los que quepan y guardar el resto para el siguiente ciclo
        dataPacket.insert_data(std::vector<uint8_t>(data.begin(), data.begin() + bytesLeft));
        args->ram.add(dataPacket.to_bytes());

        // Guardar el resto de los datos para el siguiente ciclo
        args->dataPacket = DataPacket(); // Reiniciar el paquete de datos
        args->dataPacket.insert_data(std::vector<uint8_t>(data.begin() + bytesLeft, data.end()));
    }

    usleep(STATE_GENERAL_DURATION);
}

void printVector(const std::vector<int> &vec)
{
    for (const auto &element : vec)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}
