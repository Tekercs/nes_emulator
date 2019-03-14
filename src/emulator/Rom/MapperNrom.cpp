#include "MapperNrom.h"

using namespace Emulator::ROM;
using namespace Emulator::Cpu;
using namespace Emulator::Memory;

MapperNrom::MapperNrom(const Cartridge& cartridge,
                       Emulator::Memory::Memory& memory,
                       Ppu::VRam& vram)
                       : Mapper(cartridge, memory, vram) {}

void MapperNrom::map()
{
    auto prgRomSize = this->cartridge.calcPRGRomSize();

    for (auto i = 0; i < prgRomSize; ++i)
    {
        this->memory.setAt(PRG_LOWER + i, this->cartridge.getPrgRom()[i]);
        this->memory.setAt(PRG_UPPER + i, this->cartridge.getPrgRom()[i]);
    }

    auto chrRomSize = this->cartridge.calcCHRRomSize();
    for (auto i = 0; i < PATTERN_SIZE*2; ++i)
        this->vram.writeMemory(PATTERN_0  + i, this->cartridge.getChrRom()[i]);

}
