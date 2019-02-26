#include "mapper_nrom.h"

#include <iostream>
#include <iomanip>

using namespace Emulator::ROM;
using namespace Emulator::Cpu;
using namespace Emulator::Memory;

MapperNrom::MapperNrom(const Cartridge& cartridge,
                       Emulator::Memory::Memory& memory,
                       Emulator::Cpu::Cpu& cpu)
                       : Mapper(cartridge, memory, cpu) {}

void MapperNrom::map()
{
    auto prgRomSize = this->cartridge.calcPRGRomSize();

    for (auto i = 0; i < prgRomSize; ++i)
    {
        this->memory.setAt(PRG_LOWER + i, this->cartridge.getPrgRom()[i]);
        this->memory.setAt(PRG_UPPER + i, this->cartridge.getPrgRom()[i]);
    }


}
