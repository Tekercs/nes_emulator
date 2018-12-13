#include <memory.h>
#include <cstring>
#include <iostream>
#include <algorithm>

Emulator::Memory::Memory()
{
    std::fill_n(this->memory, MEMORY_SIZE, new uint8_t(0));
}

uint8_t Emulator::Memory::getFrom(uint16_t address)
{
    return *this->memory[address];
}

void Emulator::Memory::setAt(uint16_t address, uint8_t value)
{
    *this->memory[address] = value;
}
