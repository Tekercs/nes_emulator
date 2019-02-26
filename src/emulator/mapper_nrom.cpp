#include "mapper_nrom.h"

using namespace Emulator::ROM;

MapperNrom::MapperNrom(const Cartridge &cartridge,
                       const Emulator::Memory::Memory &memory,
                       const Emulator::Cpu::Cpu &cpu)
                       : Mapper(cartridge, memory, cpu) {}

void MapperNrom::map()
{

}
