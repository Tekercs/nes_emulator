#include "Ppu.h"

#include <iostream>
#include <Utils/Converters.h>

using namespace std;
using namespace Emulator::Ppu;
using namespace Emulator::Utils;

Ppu::Ppu(std::shared_ptr<VRam> vram, std::shared_ptr<Emulator::Memory::Memory> memory)
: memory(std::move(memory))
, vram(std::move(vram))
, warmupCycles(WARMUP_CYCLES)
, cycleCounter(0)
, oamAddress(0)
, memoryAddress({.nextPart = HIGH_BYTE, .address = 0, .readBuffer = 0})
, controlFlags(DEFAULT_PPUCNTRL)
, statusFlags(DEFAULT_STATUS)
, outputMaskFlags(DEFAULT_MASKFLAGS)
{
    this->memory->subscribe(this);
}

uint8_t Ppu::getVramAddressIncrement()
{
    return (this->controlFlags & INCREMENT_BIT)? 1 : 32;
}

void Ppu::notify(initializer_list<string> parameters)
{
    std::string eventName = *parameters.begin();
    std::string param1 = "";
    std::string param2 = "";

    if (parameters.size() > 1)
        param1 = *(parameters.begin() + 1);

    if (parameters.size() > 2)
        param2 = *(parameters.begin() + 2);

    std::cout << eventName << "/" << param1 << "/" << param2 << std::endl;

    if (eventName == "memwrite" && (param1) == "2003")
    {
        this->setOAMAddress(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memwrite" && (param1) == "2004")
    {
        this->writeOAM(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memwrite" && (param1) == "4014")
    {
        this->triggerDMA((convertHexStringToInt((param2))) << 8);
        return;
    }

    if (eventName == "memwrite" && (param1) == "2006")
    {
        this->setMemoryAddress(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memwrite" && (param1) == "2007")
    {
        this->writeMemory(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memread" && (param1) == "2007")
    {
        this->readMemory();
        return;
    }

    if (eventName == "memwrite" && (param1) == "2000")
    {
        this->updateControlFlags(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memread" && (param1) == "2004")
    {
        this->readOAM();
        return;
    }

    if (eventName == "memwrite" && (param1) == "2001")
    {
        this->setOutputMaskFlags(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memread" && (param1) == "2002")
    {
        this->writeStatusToMemory();
        return;
    }

    if (eventName == "cyclepassed")
    {
        auto cyclesPassed = convertHexStringToInt(param1);
        for (uint8_t i = 0; i < cyclesPassed * 3; ++i)
            ++(*this);

        return;
    }
}

void Ppu::operator++()
{
    if (this->warmupCycles == 0)
    {
        if (this->cycleCounter == RENDER_FINISH)
        {
            // TODO render the whole screen
        }
        else if (this->cycleCounter == VBLANK_STARTS)
            this->setVblankFLag();

    }
    else
        --this->warmupCycles;

    this->cycleCounter = (this->cycleCounter +1) % MAX_CYCLE;
}

void Ppu::setVblankFLag()
{
    this->statusFlags |= VBLANK_FLAG;
    this->notifyListeners({"nmiinterrupt"});
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