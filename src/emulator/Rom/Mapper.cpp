#include "Mapper.h"

#include <memory>

#include <Rom/MapperNrom.h>

using namespace std;
using namespace Emulator::Cpu;
using namespace Emulator::Memory;
using namespace Emulator::ROM;

Mapper::Mapper(const Cartridge &cartridge
        , Emulator::Memory::Memory &memory)
: cartridge(cartridge)
, memory(memory)
{ }

shared_ptr<Mapper> Emulator::ROM::createMapper(const Cartridge &cartridge
        , Emulator::Memory::Memory &memory)
{
    auto laci = cartridge.getMapperNumber();

    switch (cartridge.getMapperNumber())
    {
        case MAPPER_NROM: return make_shared<MapperNrom>(cartridge, memory);
        default:break;
    }
}
