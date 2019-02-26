#include "mapper.h"

#include <memory>

#include <mapper_nrom.h>

using namespace std;
using namespace Emulator::Cpu;
using namespace Emulator::Memory;
using namespace Emulator::ROM;

Mapper::Mapper(const Cartridge &cartridge
        , Emulator::Memory::Memory &memory
        , Emulator::Cpu::Cpu &cpu)
: cpu(cpu)
, cartridge(cartridge)
, memory(memory)
{ }

shared_ptr<Mapper> Emulator::ROM::createMapper(const Cartridge &cartridge
        , Emulator::Memory::Memory &memory
        , Emulator::Cpu::Cpu &cpu)
{
    auto laci = cartridge.getMapperNumber();

    switch (cartridge.getMapperNumber())
    {
        case MAPPER_NROM: return make_shared<MapperNrom>(cartridge, memory, cpu);
        default:break;
    }
}
