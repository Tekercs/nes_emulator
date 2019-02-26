#include "mapper.h"

#include <memory>

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
    return shared_ptr<Mapper>();
}
