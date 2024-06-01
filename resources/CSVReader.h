// CSVReader.h
#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#define linesToRead 1

class CSVReader
{
public:
    CSVReader(const std::string &filename);
    bool getcsvFSR(std::vector<int> &fsrData);
    bool getcsvIMU(std::vector<int> &imuData);
    void CSVReader::skipLines(int n);

    bool isOpen() const;

private:
    std::ifstream file;
    std::string line;
};

#endif