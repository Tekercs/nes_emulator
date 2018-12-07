#include <memory.h>
#include <cstring>
#include <iostream>

Emulator::Memory::Memory()
{
    std::memset(this->memory, 0, sizeof(this->memory));
}

uint8_t Emulator::Memory::getMemoryFrom(uint16_t address)
{
    return 0;
}

void Emulator::Memory::setMemoryAt(uint16_t address, uint8_t value)
{
}
