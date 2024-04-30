// CSVReader.cpp
#include "CSVReader.h"

CSVReader::CSVReader(const std::string &filename) : file(filename) {}

bool CSVReader::getcsvFSR(std::vector<int> &fsrData)
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

        return true;
    }
    return false; // EOF
}

void CSVReader::getcsvIMU(std::vector<int> &imuData)
{
    std::istringstream iss(line);
    std::string token;

    // Saltar los primeros 32 números
    for (int i = 0; i < 32; ++i)
    {
        if (!std::getline(iss, token, ','))
            return; // No hay suficientes datos en la línea
    }

    // Leer los siguientes 6 números para IMU
    for (int i = 0; i < 6; ++i)
    {
        if (!std::getline(iss, token, ','))
            return; // No hay suficientes datos en la línea
        imuData.push_back(std::stoi(token));
    }
}

bool CSVReader::isOpen() const
{
    return file.is_open();
}
