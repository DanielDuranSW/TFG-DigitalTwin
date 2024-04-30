// CSVReader.cpp
#include "CSVReader.h"

CSVReader::CSVReader(const std::string &filename) : file(filename) {}

bool CSVReader::getNextLine(std::vector<int> &fsrData, std::vector<int> &imuData)
{
    std::string line;
    if (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;

        for (int i = 0; i < 32; ++i)
        {
            std::getline(iss, token, ',');
            fsrData.push_back(std::stoi(token));
        }

        // Leer el resto de los números para IMU
        while (std::getline(iss, token, ','))
        {
            imuData.push_back(std::stoi(token));
        }

        return true;
    }
    return false; // EOF
}

bool CSVReader::isOpen() const
{
    return file.is_open();
}