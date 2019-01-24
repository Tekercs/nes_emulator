#include "cartridge.h"

#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>

Emulator::Cartridge::Cartridge(const std::string &path)
{
    std::ifstream input(path, std::ios::binary);

    std::istream_iterator<uint8_t> iterator(input);

    // read the header
    uint8_t header[HEADER_LENGTH];
    for (uint8_t &i : header)
    {
        i = *iterator;
        ++iterator;
    }

    // read the trainer
    bool isTrainerPresented = ((header[6] & 0x04 ) > 0);
    if (isTrainerPresented)
    {
        uint8_t trainer[TRAINER_LENGTH];
        for (uint8_t &i : trainer)
        {
            i = *iterator;
            ++iterator;
        }
    }

    // read the PRG rom size
    uint16_t prgRomSize16KBBatch = 0;
    prgRomSize16KBBatch = header[9] & 0b00001111; // first 4 bit from header byte 9 as MSB
    prgRomSize16KBBatch = prgRomSize16KBBatch << 8;
    prgRomSize16KBBatch += header[4]; // the while header byte 4 as LSB

    int prgRomSize = 16384 * prgRomSize16KBBatch;

    // read the actual PRG rom content
    uint8_t prgRom[prgRomSize];
    for (uint8_t &i : prgRom)
    {
        i = *iterator;
        ++iterator;
    }

     // read the CHR rom size
    uint16_t chrRomSize8KByteBatch = 0;
    chrRomSize8KByteBatch = header[9] & 0b11110000; // first 4 bit from header byte 9 as MSB
    chrRomSize8KByteBatch = chrRomSize8KByteBatch << 8;
    chrRomSize8KByteBatch += header[5]; // the while header byte 6 as LSB

    int chrRomSize = 8192 * chrRomSize8KByteBatch;

    // read the actual CHR rom content
    uint8_t chrRom[chrRomSize];
    for (uint8_t &i : chrRom)
    {
        i = *iterator;
        ++iterator;
    }
}
