// CSVReader.cpp
#include "CSVReader.h"

CSVReader::CSVReader(const std::string &filename) : file(filename) {}

bool CSVReader::getcsvFSR(std::vector<int> &fsrData)
{
    for (int lineCount = 0; lineCount < linesToRead; lineCount++)
    {
        if (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string token;

            for (int i = 0; i < 32; ++i)
            {
                if (!std::getline(iss, token, ','))
                    return false; // No hay suficientes datos en la línea

                fsrData.push_back(std::stoi(token));
            }
        }
        else
        {
            printf("Total consumido: %f\n", INTENSITY_CONSUMED);
            terminateFlag = true;
        }
    }
    return true;
}

bool CSVReader::getcsvIMU(std::vector<int> &imuData)
{
    for (int lineCount = 0; lineCount < linesToRead; lineCount++)
    {
        if (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string token;

            // Saltar los primeros 32 números
            for (int i = 0; i < 32; ++i)
            {
                if (!std::getline(iss, token, ','))
                    return false; // No hay suficientes datos en la línea
            }

            // Leer los siguientes 6 números para IMU
            for (int i = 0; i < 6; ++i)
            {
                if (!std::getline(iss, token, ','))
                    return false; // No hay suficientes datos en la línea
                imuData.push_back(std::stoi(token));
            }
        }
    }
    return true;
}
void CSVReader::skipLines(int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (!std::getline(file, line))
        {
            // printf("Total consumido: %f\n", INTENSITY_CONSUMED);
            break; // Si no hay suficientes líneas, sal del bucle
        }
    }
}

bool CSVReader::isOpen() const
{
    return file.is_open();
}
