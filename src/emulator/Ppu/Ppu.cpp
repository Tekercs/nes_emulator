#include "Ppu.h"

#include <Utils/Converters.h>

using namespace std;
using namespace Emulator::Ppu;
using namespace Emulator::Utils;

Ppu::Ppu(std::shared_ptr<VRam> vram, std::shared_ptr<Emulator::Memory::Memory> memory)
: memory(std::move(memory))
, vram(std::move(vram))
{
    this->oamAccessor.address = 0;
    this->oamAccessor.value = 0;

    this->memory->subscribe(this);
}

void Ppu::notify(initializer_list<string> parameters)
{
    if (*parameters.begin() == "memwrite")
        if ((*(parameters.begin() +1)) == "2003")
            this->oamAccessor.address = static_cast<uint8_t>(convertHexStringToInt(*(parameters.begin() + 2)));


    if (*parameters.begin() == "memwrite")
        if ((*(parameters.begin() +1)) == "2004")
        {
            this->oamAccessor.value = static_cast<uint8_t>(convertHexStringToInt(*(parameters.begin() + 2)));
            this->vram->writeOAM(this->oamAccessor.address, this->oamAccessor.value);

            ++this->oamAccessor.address;
        }

    if (*parameters.begin() == "memwrite")
        if ((*(parameters.begin() + 1)) == "4014")
        {
            uint16_t memoryPrefix = (convertHexStringToInt((*(parameters.begin() + 2)))) << 8;

            for (auto i = 0; i < OAM_SIZE; ++i)
            {
                this->vram->writeOAM(this->oamAccessor.address, this->memory->getFrom(memoryPrefix + i));
                ++this->oamAccessor.address;
            }
        }

    if (*parameters.begin() == "memread")
        if ((*(parameters.begin() + 1)) == "2004")
        {
            auto result = this->vram->readOAM(this->oamAccessor.address);
            this->memory->setAt(0x2004, result);
        }
}