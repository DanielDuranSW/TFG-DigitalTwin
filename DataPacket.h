#ifndef DATAPACKET_H
#define DATAPACKET_H

#include <vector>
#include <cstdint>
#include <stdexcept>

#define DATA_PACKET_SIZE 512

class DataPacket
{
public:
    // Constructor
    DataPacket();

    // Métodos
    void insert_data(const std::vector<uint8_t> &data);
    size_t getBytesLeft();
    std::vector<uint8_t> to_bytes() const;

private:
    // Constantes
    static const int TOKEN_VALUE = 0b11111110;            // 254
    static const uint16_t CRC_VALUE = 0b1111111111111111; // 65535
    static const uint8_t DUMMY_BYTE = 0b11111111;         // 255

    uint8_t token;
    uint16_t crc;
    uint8_t dummy;

    // Variables miembro
    std::vector<uint8_t> data;
    std::vector<uint8_t> dataLeft;
    size_t bytesLeft;

    size_t index;
    size_t endIndex;
};

#endif // DATAPACKET_H
