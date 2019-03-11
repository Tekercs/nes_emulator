#include "Ppu.h"

#include <Utils/Converters.h>

using namespace std;
using namespace Emulator::Ppu;
using namespace Emulator::Utils;

Ppu::Ppu(std::shared_ptr<VRam> vram, std::shared_ptr<Emulator::Memory::Memory> memory)
: memory(std::move(memory))
, vram(std::move(vram))
{
    this->oamAccessor.adress = 0;
    this->oamAccessor.value = 0;

    this->memory->subscribe(this);
}

void Ppu::notify(initializer_list<string> parameters)
{
    if (*parameters.begin() == "memwrite")
        if ((*(parameters.begin() +1)) == "2003")
            this->oamAccessor.adress = static_cast<uint8_t>(convertHexStringToInt(*(parameters.begin() + 2)));


    if (*parameters.begin() == "memwrite")
        if ((*(parameters.begin() +1)) == "2004")
        {
            this->oamAccessor.value = static_cast<uint8_t>(convertHexStringToInt(*(parameters.begin() + 2)));
            this->vram->writeOAM(this->oamAccessor.adress, this->oamAccessor.value);
            auto laci = "breakpoint";
        }
}