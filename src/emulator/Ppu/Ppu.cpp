#include "Ppu.h"

#include <Utils/Converters.h>

using namespace std;
using namespace Emulator::Ppu;
using namespace Emulator::Utils;

Ppu::Ppu(std::shared_ptr<VRam> vram, std::shared_ptr<Emulator::Memory::Memory> memory)
: memory(std::move(memory))
, vram(std::move(vram))
{
    this->oamAddress = 0;
    this->memoryAddress = {.nextPart = HIGH_BYTE, .address = 0, .readBuffer = 0};

    this->memory->subscribe(this);

    this->controlFlags = DEFAULT_PPUCNTRL;
    this->outputMaskFlags = DEFAULT_MASKFLAGS;
    this->statusFlags = DEFAULT_STATUS;
}

uint8_t Ppu::getVramAddressIncrement()
{
    return (this->controlFlags & INCREMENT_BIT)? 1 : 32;
}

void Ppu::notify(initializer_list<string> parameters)
{

    if (*parameters.begin() == "memwrite" && (*(parameters.begin() +1)) == "2003")
    {
        this->setOAMAddress(convertHexStringToInt(*(parameters.begin() + 2)));
        return;
    }

    if (*parameters.begin() == "memwrite" && (*(parameters.begin() +1)) == "2004")
    {
        this->writeOAM(convertHexStringToInt(*(parameters.begin() + 2)));
        return;
    }

    if (*parameters.begin() == "memwrite" && (*(parameters.begin() + 1)) == "4014")
    {
        this->triggerDMA((convertHexStringToInt((*(parameters.begin() + 2)))) << 8);
        return;
    }

    if (*parameters.begin() == "memwrite" && (*(parameters.begin() + 1)) == "2006")
    {
        this->setMemoryAddress(convertHexStringToInt(*(parameters.begin() + 2)));
        return;
    }

    if (*parameters.begin() == "memwrite" && (*(parameters.begin() + 1)) == "2007")
    {
        this->writeMemory(convertHexStringToInt(*(parameters.begin() + 2)));
        return;
    }

    if (*parameters.begin() == "memread" && (*(parameters.begin() + 1)) == "2007")
    {
        this->readMemory();
        return;
    }

    if (*parameters.begin() == "memwrite" && (*(parameters.begin() + 1)) == "2000")
    {
        this->updateControlFlags(convertHexStringToInt(*(parameters.begin() + 2)));
        return;
    }

    if (*parameters.begin() == "memread" && (*(parameters.begin() + 1)) == "2004")
    {
        this->readOAM();
        return;
    }

    if (*parameters.begin() == "memwrite" && (*(parameters.begin() + 1)) == "2001")
    {
        this->setOutputMaskFlags(convertHexStringToInt(*(parameters.begin() + 2)));
        return;
    }

    if (*parameters.begin() == "memread" && (*(parameters.begin() + 1)) == "2002")
    {
        this->writeStatusToMemory();
        return;
    }
}

void Ppu::writeStatusToMemory()
{
    this->memory->setAt(0x2002, this->statusFlags);
    this->statusFlags = this->statusFlags & 0b01111111;

    switch (this->controlFlags & 0b00000011)
    {
        case 0: this->memoryAddress.address = NAME_0;
        case 1: this->memoryAddress.address = NAME_1;
        case 2: this->memoryAddress.address = NAME_2;
        case 3: this->memoryAddress.address = NAME_3;
    }
}

void Ppu::setOutputMaskFlags(uint8_t maskFlags)
{
    this->outputMaskFlags = maskFlags;
}

void Ppu::setOAMAddress(uint8_t address)
{
    this->oamAddress = address;
}

void Ppu::writeOAM(uint8_t data)
{
    this->vram->writeOAM(this->oamAddress, data);

    ++this->oamAddress;
}


void Ppu::triggerDMA(uint8_t memoryPrefix)
{
    for (auto i = 0; i < OAM_SIZE; ++i)
    {
        this->vram->writeOAM(this->oamAddress, this->memory->getFrom(memoryPrefix + i));
        ++this->oamAddress;
    }
}


void Ppu::setMemoryAddress(uint8_t addressPart)
{
    this->memoryAddress.address = (this->memoryAddress.nextPart == LOW_BYTE)
        ? (this->memoryAddress.address & 0xFF00) + addressPart
        : (this->memoryAddress.address & 0x00FF) + ((addressPart % 0x40) << 8);

    this->memoryAddress.nextPart = (this->memoryAddress.nextPart == LOW_BYTE) ? HIGH_BYTE : LOW_BYTE;
}


void Ppu::writeMemory(uint8_t data)
{
    this->vram->writeMemory(this->memoryAddress.address, data);

    this->memoryAddress.address += this->getVramAddressIncrement();
}

void Ppu::readMemory()
{
    uint8_t workingAddress = this->memoryAddress.address % VRAM_SIZE;

    if (workingAddress < PALETTE_STARTS)
    {
        this->memory->setAt(0x2007, this->memoryAddress.readBuffer);
        this->memoryAddress.readBuffer = this->vram->readMemory(workingAddress);
    }
    else
    {
        this->memory->setAt(0x2007, this->vram->readMemory(workingAddress));

        uint8_t newAddress = VRAM_SIZE + (workingAddress - PALETTE_STARTS) % VRAM_SIZE;
        this->memoryAddress.readBuffer = vram->readMemory(newAddress);
    }

    this->memoryAddress.address += this->getVramAddressIncrement();
}

void Ppu::updateControlFlags(uint8_t newValue)
{
    this->controlFlags = newValue;
}

void Ppu::readOAM()
{
    auto result = this->vram->readOAM(this->oamAddress);
    this->memory->setAt(0x2004, result);
}