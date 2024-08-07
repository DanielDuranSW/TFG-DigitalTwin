#include "DataPacket.h"
#include <iostream>

DataPacket::DataPacket() : token(TOKEN_VALUE), crc(CRC_VALUE), dummy(DUMMY_BYTE)
{
    // Inicialización de los valores de configuración
    bytesLeft = DATA_PACKET_SIZE;
    index = 0;
    data.resize(DATA_PACKET_SIZE, 0);
}

void DataPacket::insert_data(const std::vector<uint8_t> &byte_data)
{
    size_t dataLength = byte_data.size();
    size_t endIndex = index + dataLength;

    for (size_t i = 0; i < dataLength; ++i)
    {
        if (index >= DATA_PACKET_SIZE)
        {
            break;
        }
        data[index++] = byte_data[i];
    }

    index = endIndex;
    bytesLeft -= dataLength;
}

std::vector<uint8_t> DataPacket::to_bytes() const
{
    // Empaquetar los datos en un vector de bytes según el formato especificado
    std::vector<uint8_t> packet;
    packet.reserve(DATA_PACKET_SIZE);

    // Insertar el token
    packet.push_back(token);

    // Insertar los datos
    packet.insert(packet.end(), data.begin(), data.end());

    packet.push_back((crc >> 8) & 0xFF);
    packet.push_back(crc & 0xFF);

    // Insertar el byte dummy
    packet.push_back(dummy);

    return packet;
}

size_t DataPacket::getBytesLeft()
{
    return bytesLeft;
}