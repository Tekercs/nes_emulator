#include "VRam.h"

#include <algorithm>
#include <iterator>

using namespace std;
using namespace Emulator::Ppu;

VRam::VRam(NametableMirroring mirroringType)
{
    generate(begin(this->memory), end(this->memory), []() { return new uint8_t(0); });
    generate(begin(this->oam), end(this->oam), []() { return new uint8_t(0); });

    this->generateNametable(mirroringType);
    this->generatePaletteRam();
}

void VRam::generateNametable(NametableMirroring mirroringType)
{
    uint8_t* nametable1[NAME_SIZE] = {};
    uint8_t* nametable2[NAME_SIZE] = {};

    generate(begin(nametable1), end(nametable1), []() { return new uint8_t(0); });
    generate(begin(nametable1), end(nametable2), []() { return new uint8_t(0); });

    uint8_t* nametables[NAME_SIZE * 4] = {};

    if (mirroringType == HORIZONTAL)
    {
        copy(begin(nametable1), end(nametable1), begin(nametables));
        copy(begin(nametable1), end(nametable1), begin(nametables) + NAME_SIZE);
        copy(begin(nametable2), end(nametable2), begin(nametables) + (NAME_SIZE * 2));
        copy(begin(nametable2), end(nametable2), begin(nametables) + (NAME_SIZE * 3));
    }
    else if (mirroringType == VERTICAL)
    {
        copy(begin(nametable1), end(nametable1), begin(nametables));
        copy(begin(nametable2), end(nametable2), begin(nametables) + NAME_SIZE);
        copy(begin(nametable1), end(nametable1), begin(nametables) + (NAME_SIZE * 2));
        copy(begin(nametable2), end(nametable2), begin(nametables) + (NAME_SIZE * 3));
    }

    copy(begin(nametables), end(nametables), begin(this->memory) + NAME_0);
    copy(begin(nametables), end(nametables), begin(this->memory) + NAME_MIRRORING_STARTS);
}

void VRam::generatePaletteRam()
{
    uint8_t* paletteRam[PALETTE_SIZE] = {};
    generate(begin(paletteRam), end(paletteRam), []() { return new uint8_t(0); });

    for (auto i = 0; i < PALETTE_TOTAL + 1; ++i)
        copy(begin(paletteRam), end(paletteRam), begin(this->memory) + PALETTE_STARTS + (PALETTE_SIZE * i) );
}

uint8_t VRam::readOAM(uint8_t address)
{
    return *this->oam[address];
}

void VRam::writeOAM(uint8_t address, uint8_t value)
{
    *this->oam[address] = value;
}

uint8_t VRam::readMemory(uint16_t address)
{
    auto tempAddress = address % VRAM_SIZE;

    return *this->memory[tempAddress];
}

void VRam::writeMemory(uint16_t address, uint8_t value)
{
    auto tempAddress = address % VRAM_SIZE;

    *this->memory[tempAddress] = value;
}