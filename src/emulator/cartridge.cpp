#include "cartridge.h"

#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Emulator::Cartridge::Cartridge(const std::string &path)
{
    std::ifstream input(path, std::ios::binary);
    input.seekg(0, input.end);
    auto length = input.tellg();
    input.seekg(0, input.beg);

    std::istreambuf_iterator<char> iterator(input);

    this->readHeader(&input);

    // read the trainer
    bool isTrainerPresented = ((this->rawHeader[6] & 0x04 ) > 0);
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
    uint32_t prgRomSize = 0;
    prgRomSize16KBBatch = this->rawHeader[9] & 0b00001111; // first 4 bit from this->rawHeader byte 9 as MSB
    if (prgRomSize16KBBatch == 0xF)
    {
        uint8_t exponent = (this->rawHeader[4] & 0b11111100) >> 2;
        uint8_t multipiler = this->rawHeader[4] & 0b00000011;

        prgRomSize = std::pow(2, exponent) * (multipiler * 2 + 1);
    }
    else
    {
        prgRomSize16KBBatch = prgRomSize16KBBatch << 8;
        prgRomSize16KBBatch += this->rawHeader[4]; // the while this->rawHeader byte 4 as LSB

        prgRomSize = 16384 * prgRomSize16KBBatch;
    }

    // read the actual PRG rom content
    uint8_t prgRom[prgRomSize];
    for (uint8_t &i : prgRom)
    {
        i = *iterator;
        ++iterator;
    }

    // read the CHR rom size
    uint32_t chrRomSize = 0;
    uint16_t chrRomSize8KByteBatch = 0;
    chrRomSize8KByteBatch = this->rawHeader[9] & 0b11110000; // last 4 bit from this->rawHeader byte 9 as MSB
    if ((chrRomSize8KByteBatch >> 4) == 0xF)
    {
        uint8_t exponent = (this->rawHeader[5] & 0b11111100) >> 2;
        uint8_t multipiler = this->rawHeader[5] & 0b00000011;

        chrRomSize = std::pow(2, exponent) * (multipiler * 2 + 1);
    }
    else
    {
        chrRomSize8KByteBatch = chrRomSize8KByteBatch << 4;
        chrRomSize8KByteBatch += this->rawHeader[5]; // the while header byte 6 as LSB

        chrRomSize = 8192 * chrRomSize8KByteBatch;
    }

    // read the actual CHR rom content
    uint8_t chrRom[chrRomSize];
    for (uint8_t &i : chrRom)
    {
        i = *iterator;
        ++iterator;
    }

    // calc miscrom size
    auto miscRomSize = length - input.tellg();
    uint8_t miscRom[miscRomSize];

    // read in the actual misc rom
    for (uint8_t &i : miscRom)
    {
        i = *iterator;
        ++iterator;
    }

    input.close();
}

void Emulator::Cartridge::readHeader(std::ifstream* file)
{
    file->seekg(HEADER_STARTS, ifstream::beg);
    istreambuf_iterator<char> iterator(*file);

    for (uint8_t &i : this->rawHeader)
    {
        i = *iterator;
        ++iterator;
    }
}
