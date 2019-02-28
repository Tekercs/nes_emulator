#include "Cartridge.h"

#include <fstream>
#include <cmath>

using namespace std;

Emulator::ROM::Cartridge::Cartridge(const std::string &path)
{
    ifstream input(path, ios::binary);

    this->readHeader(&input);
    this->parseHeader();

    this->readTrainer(&input);

    this->readPRGRom(&input);
    this->readCHRRom(&input);
    this->readMiscRom(&input);

    input.close();
}

void Emulator::ROM::Cartridge::readHeader(std::ifstream* file)
{
    file->seekg(HEADER_STARTS, ifstream::beg);
    istreambuf_iterator<char> iterator(*file);

    for (uint8_t &i : rawHeader)
    {
        i = *iterator;
        ++iterator;
    }
}

void Emulator::ROM::Cartridge::parseHeader()
{
    this->isTrainerPresent = ((this->rawHeader[6] & 0x04 ) > 0);
}

void Emulator::ROM::Cartridge::readTrainer(std::ifstream* file)
{
    if (this->isTrainerPresent)
    {
        file->seekg(0 + HEADER_LENGTH, ifstream::beg);
        istreambuf_iterator<char> iterator(*file);

        for (uint8_t &i : trainer)
        {
            i = *iterator;
            ++iterator;
        }
    }
}

void Emulator::ROM::Cartridge::readPRGRom(std::ifstream *file)
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

uint32_t Emulator::ROM::Cartridge::calcPRGRomSize() const
{
    uint16_t prgRomSize16KBBatch = 0;
    prgRomSize16KBBatch = this->rawHeader[9] & 0b00001111;
    if (prgRomSize16KBBatch == 0xF)
    {
        uint8_t exponent = (this->rawHeader[4] & 0b11111100) >> 2;
        uint8_t multipiler = this->rawHeader[4] & 0b00000011;

        return pow(2, exponent) * (multipiler * 2 + 1);
    }
    else
    {
        prgRomSize16KBBatch = prgRomSize16KBBatch << 8;
        prgRomSize16KBBatch += this->rawHeader[4];

        return 16384 * prgRomSize16KBBatch;
    }
}

void Emulator::ROM::Cartridge::readCHRRom(std::ifstream *file)
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

uint32_t Emulator::ROM::Cartridge::calcCHRRomSize() const
{
    uint16_t chrRomSize8KByteBatch = 0;
    chrRomSize8KByteBatch = this->rawHeader[9] & 0b11110000;
    if ((chrRomSize8KByteBatch >> 4) == 0xF)
    {
        uint8_t exponent = (this->rawHeader[5] & 0b11111100) >> 2;
        uint8_t multipiler = this->rawHeader[5] & 0b00000011;

        return pow(2, exponent) * (multipiler * 2 + 1);
    }
    else
    {
        chrRomSize8KByteBatch = chrRomSize8KByteBatch << 4;
        chrRomSize8KByteBatch += this->rawHeader[5];

        return 8192 * chrRomSize8KByteBatch;
    }
}

void Emulator::ROM::Cartridge::readMiscRom(std::ifstream *file)
{
    auto miscRomPosition = 0 + HEADER_LENGTH + this->calcPRGRomSize() + this->calcCHRRomSize();
    if (this->isTrainerPresent)
        miscRomPosition += TRAINER_LENGTH;

    file->seekg(0, ifstream::end);
    auto length = file->tellg();

    file->seekg(miscRomPosition, ifstream::beg);
    istreambuf_iterator<char> iterator(*file);

    this->miscRomSize = length - file->tellg();
    this->miscRom = new uint8_t[this->miscRomSize];
    for (auto i = 0; i < this->miscRomSize; ++i)
    {
        this->miscRom[i] = *iterator;
        ++iterator;
    }
}

const uint8_t* Emulator::ROM::Cartridge::getRawHeader() const
{
    return this->rawHeader;
}

const uint8_t* Emulator::ROM::Cartridge::getMiscRom() const
{
    return this->miscRom;
}

const uint8_t* Emulator::ROM::Cartridge::getPrgRom() const
{
    return this->prgRom;
}

const uint8_t* Emulator::ROM::Cartridge::getChrRom() const
{
    return this->chrRom;
}

const uint8_t* Emulator::ROM::Cartridge::getTrainer() const
{
    return this->trainer;
}

uint32_t Emulator::ROM::Cartridge::getMiscRomSize() const
{
    return this->miscRomSize;
}

bool Emulator::ROM::Cartridge::trainerExists() const
{
    return this->isTrainerPresent;
}

uint8_t Emulator::ROM::Cartridge::getMapperNumber() const
{
    uint8_t mapperNumber = 0x00;

    mapperNumber = this->rawHeader[7] & 0b11110000;
    mapperNumber += this->rawHeader[6] & 0b00001111;

    return mapperNumber;
}

