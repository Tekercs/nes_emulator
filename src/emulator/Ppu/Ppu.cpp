#include "Ppu.h"

#include <Utils/Converters.h>

using namespace std;
using namespace Emulator::Ppu;
using namespace Emulator::Utils;

Ppu::Ppu(std::shared_ptr<VRam> vram, std::shared_ptr<Emulator::Memory::Memory> memory)
: memory(std::move(memory))
, vram(std::move(vram))
{
    this->oamAddress = 0;
    this->memoryAddress = {.nextPart = HIGH_BYTE, .address = 0};

    this->memory->subscribe(this);

    this->ppuControl = DEFAULT_PPUCNTRL;
}

uint8_t Ppu::getVramAddressIncrement()
{
    return (this->ppuControl & INCREMENT_BIT)? 1 : 32;
}

void Ppu::notify(initializer_list<string> parameters)
{
    // TODO concat param1 and param2  and write a switch statement for that

    if (*parameters.begin() == "memwrite")
        if ((*(parameters.begin() +1)) == "2003")
            this->oamAddress = static_cast<uint8_t>(convertHexStringToInt(*(parameters.begin() + 2)));


    if (*parameters.begin() == "memwrite")
        if ((*(parameters.begin() +1)) == "2004")
        {
            this->vram->writeOAM(this->oamAddress, static_cast<uint8_t>(convertHexStringToInt(*(parameters.begin() + 2))));

            ++this->oamAddress;
        }

    if (*parameters.begin() == "memwrite")
        if ((*(parameters.begin() + 1)) == "4014")
        {
            uint16_t memoryPrefix = (convertHexStringToInt((*(parameters.begin() + 2)))) << 8;

            for (auto i = 0; i < OAM_SIZE; ++i)
            {
                this->vram->writeOAM(this->oamAddress, this->memory->getFrom(memoryPrefix + i));
                ++this->oamAddress;
            }
        }

    if (*parameters.begin() == "memwrite")
        if ((*(parameters.begin() + 1)) == "2006")
        {
            this->memoryAddress.address = (this->memoryAddress.nextPart == LOW_BYTE) 
                ? (this->memoryAddress.address & 0xFF00) + convertHexStringToInt(*(parameters.begin() + 2))
                : (this->memoryAddress.address & 0x00FF) + ((convertHexStringToInt(*(parameters.begin() + 2)) % 0x40) << 8);

            this->memoryAddress.nextPart = (this->memoryAddress.nextPart == LOW_BYTE) ? HIGH_BYTE : LOW_BYTE;
        }

    if (*parameters.begin() == "memwrite")
        if ((*(parameters.begin() + 1)) == "2007")
        {
            uint8_t data = convertHexStringToInt(*(parameters.begin() + 2));
            this->vram->writeMemory(this->memoryAddress.address, data);

            this->memoryAddress.address += this->getVramAddressIncrement();
        }

    if (*parameters.begin() == "memwrite")
        if ((*(parameters.begin() + 1)) == "2000")
        {
            this->ppuControl = convertHexStringToInt(*(parameters.begin() + 2));
        }

    if (*parameters.begin() == "memread")
        if ((*(parameters.begin() + 1)) == "2004")
        {
            auto result = this->vram->readOAM(this->oamAddress);
            this->memory->setAt(0x2004, result);
        }
}