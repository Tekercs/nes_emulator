#include <Memory/Memory.h>
#include <cstring>
#include <iterator>
#include <algorithm>

#include <Utils/Converters.h>

using namespace std;
using namespace Emulator::Memory;
using namespace Emulator::Utils;

Memory::Memory()
{
    generate(begin(this->memory), end(this->memory), []() { return new uint8_t(0); });

    this->generateRAM();
    this->generateIORegisters();
}

void Memory::generateRAM()
{
    uint8_t* ram[RAM_MIRROR] = {};
    generate(begin(ram), end(ram), []() { return new uint8_t(0); });

    copy(begin(ram), end(ram), begin(this->memory));
    copy(begin(ram), end(ram), begin(this->memory) + RAM_MIRROR);
    copy(begin(ram), end(ram), begin(this->memory) + (RAM_MIRROR *2));
    copy(begin(ram), end(ram), begin(this->memory) + (RAM_MIRROR *3));
}

void Memory::generateIORegisters()
{
    uint8_t* ioRegisters[IO_REGISTERS_SIZE];
    generate(begin(ioRegisters), end(ioRegisters), []() { return new uint8_t(0); });

    copy(begin(ioRegisters), end(ioRegisters), begin(this->memory) + IO_REGISTERS);
    for(auto i = IO_REGISTERS_MIRROR; i < IO_REGISTERS_SEC; i += IO_REGISTERS_SIZE)
        copy(begin(ioRegisters), end(ioRegisters), begin(this->memory) + i);
}


uint8_t Memory::getFrom(uint16_t address)
{
    this->notifyListeners({"memread", convertIntToHexString(address)});
    return *this->memory[address];
}

void Memory::setAt(uint16_t address, uint8_t value)
{
    if (address == 0x2000)
    {
        auto laci = 1;
        auto laci2 = 2;
    }

    this->notifyListeners({"memwrite", convertIntToHexString(address), convertIntToHexString(value)});
    *this->memory[address] = value;
}
