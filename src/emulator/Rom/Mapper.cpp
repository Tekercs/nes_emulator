#include "Mapper.h"

#include <memory>

#include <Rom/MapperNrom.h>

using namespace std;
using namespace Emulator::Cpu;
using namespace Emulator::Memory;
using namespace Emulator::ROM;
using namespace Emulator::Ppu;

Mapper::Mapper(const Cartridge &cartridge
        , Emulator::Memory::Memory &memory
        , Emulator::Ppu::VRam &vram)
: cartridge(cartridge)
, memory(memory)
, vram(vram)
{ }

shared_ptr<Mapper> Emulator::ROM::createMapper(const Cartridge &cartridge
        , Emulator::Memory::Memory &memory
        , VRam &vram)
{
    auto laci = cartridge.getMapperNumber();

    switch (cartridge.getMapperNumber())
    {
        case MAPPER_NROM: return make_shared<MapperNrom>(cartridge, memory,  vram);
        default:break;
    }
}
