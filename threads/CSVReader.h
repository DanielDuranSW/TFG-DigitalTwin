// CSVReader.h
#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class CSVReader
{
public:
    CSVReader(const std::string &filename);
    bool getcsvFSR(std::vector<int> &fsrData);
    void getcsvIMU(std::vector<int> &imuData);

    bool isOpen() const;

private:
    std::ifstream file;
    std::string line;
};

#endif