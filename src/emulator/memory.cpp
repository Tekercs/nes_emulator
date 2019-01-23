#include <memory.h>
#include <cstring>
#include <iostream>
#include <algorithm>

Emulator::Memory::Memory()
{
    std::generate(std::begin(this->memory), std::end(this->memory), []() { return new uint8_t(0); });

    this->generateRAM();
    this->generateIORegisters();
}

void Emulator::Memory::generateRAM()
{
    uint8_t* ram[RAM_MIRROR] = {};
    std::generate(std::begin(ram), std::end(ram), []() { return new uint8_t(0); });

    std::copy(std::begin(ram), std::end(ram), std::begin(this->memory));
    std::copy(std::begin(ram), std::end(ram), std::begin(this->memory) + RAM_MIRROR);
    std::copy(std::begin(ram), std::end(ram), std::begin(this->memory) + (RAM_MIRROR *2));
    std::copy(std::begin(ram), std::end(ram), std::begin(this->memory) + (RAM_MIRROR *3));
}

void Emulator::Memory::generateIORegisters()
{
    uint8_t* ioRegisters[IO_REGISTERS_SIZE];
    std::generate(std::begin(ioRegisters), std::end(ioRegisters), []() { return new uint8_t(0); });

    std::copy(std::begin(ioRegisters), std::end(ioRegisters), std::begin(this->memory) + IO_REGISTERS);
    for(auto i = IO_REGISTERS_MIRROR; i < IO_REGISTERS_SEC; i += IO_REGISTERS_SIZE)
        std::copy(std::begin(ioRegisters), std::end(ioRegisters), std::begin(this->memory) + i);
}


uint8_t Emulator::Memory::getFrom(uint16_t address)
{
    return *this->memory[address];
}

void Emulator::Memory::setAt(uint16_t address, uint8_t value)
{
    *this->memory[address] = value;
}
