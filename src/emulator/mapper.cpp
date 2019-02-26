#include "mapper.h"

#include <memory>

#include <mapper_nrom.h>

using namespace std;
using namespace Emulator::Cpu;
using namespace Emulator::Memory;
using namespace Emulator::ROM;

Mapper::Mapper(const Cartridge &cartridge
        , const Emulator::Memory::Memory &memory
        , const Emulator::Cpu::Cpu &cpu)
: cpu(cpu)
, cartridge(cartridge)
, memory(memory)
{ }

shared_ptr<Mapper> createMapper(const Cartridge &cartridge
        , const Memory &memory
        , const Cpu &cpu)
{
    switch (cartridge.getMapperNumber())
    {
        case MAPPER_NROM: make_shared<MapperNrom>(cartridge, memory, cpu);
        default:break;
    }

    return shared_ptr<Mapper>();
}
