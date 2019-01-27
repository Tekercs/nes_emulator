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
    this->parseHeader();

    this->readTrainer(&input);

    this->readPRGRom(&input);

    
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

void Emulator::Cartridge::parseHeader()
{
    this->isTrainerPresent = ((this->rawHeader[6] & 0x04 ) > 0);
}

void Emulator::Cartridge::readTrainer(std::ifstream* file)
{
    if (this->isTrainerPresent)
    {
        file->seekg(0 + HEADER_LENGTH, ifstream::beg);
        istreambuf_iterator iterator(*file);
        for (uint8_t &i : this->trainer)
        {
            i = *iterator;
            ++iterator;
        }
    }
}

void Emulator::Cartridge::readPRGRom(std::ifstream *file)
{
    auto prgRomPosition = 0 + HEADER_LENGTH;
    if (this->isTrainerPresent)
        prgRomPosition += TRAINER_LENGTH;

    file->seekg(prgRomPosition, ifstream::beg);
    istreambuf_iterator<char> iterator(*file);

    auto prgRomSize = this->calcPRGRomSize();
    this->prgRom = new uint8_t[prgRomSize];
    for (auto i = 0; i < prgRomSize; ++i)
    {
        this->prgRom[i] = *iterator;
        ++iterator;
    }

}

uint32_t Emulator::Cartridge::calcPRGRomSize()
{
    uint16_t prgRomSize16KBBatch = 0;
    prgRomSize16KBBatch = this->rawHeader[9] & 0b00001111;
    if (prgRomSize16KBBatch == 0xF)
    {
        uint8_t exponent = (this->rawHeader[4] & 0b11111100) >> 2;
        uint8_t multipiler = this->rawHeader[4] & 0b00000011;

        return std::pow(2, exponent) * (multipiler * 2 + 1);
    }
    else
    {
        prgRomSize16KBBatch = prgRomSize16KBBatch << 8;
        prgRomSize16KBBatch += this->rawHeader[4];

        return 16384 * prgRomSize16KBBatch;
    }
}

void Emulator::Cartridge::readCHRRom(std::ifstream *file)
{
    auto chrRomPosition = 0 + HEADER_LENGTH + this->calcPRGRomSize();
    if (this->isTrainerPresent)
        chrRomPosition += TRAINER_LENGTH;

    file->seekg(chrRomPosition, ifstream::beg);
    istreambuf_iterator<char> iterator(*file);
    
    auto chrRomSize = this->calcCHRRomSize();
    this->chrRom = new uint8_t[chrRomSize];
    for(auto i = 0; i < chrRomSize; ++i)
    {
        chrRom[i] = *iterator;
        ++iterator;
    }
}

uint32_t Emulator::Cartridge::calcCHRRomSize()
{
    uint16_t chrRomSize8KByteBatch = 0;
    chrRomSize8KByteBatch = this->rawHeader[9] & 0b11110000;
    if ((chrRomSize8KByteBatch >> 4) == 0xF)
    {
        uint8_t exponent = (this->rawHeader[5] & 0b11111100) >> 2;
        uint8_t multipiler = this->rawHeader[5] & 0b00000011;

        return std::pow(2, exponent) * (multipiler * 2 + 1);
    }
    else
    {
        chrRomSize8KByteBatch = chrRomSize8KByteBatch << 4;
        chrRomSize8KByteBatch += this->rawHeader[5];

        return 8192 * chrRomSize8KByteBatch;
    }
}

