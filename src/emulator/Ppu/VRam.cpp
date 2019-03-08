#include "VRam.h"

#include <algorithm>
#include <iterator>

using namespace std;
using namespace Emulator::Ppu;

VRam::VRam()
{
    generate(begin(this->memory), end(this->memory), []() { return new uint8_t(0); });
    generate(begin(this->oam), end(this->oam), []() { return 0; });

    this->generateNametable();
    this->generatePaletteRam();
}

void VRam::generateNametable()
{
    uint8_t* nametables[NAME_SIZE * 4] = {};
    generate(begin(nametables), end(nametables), []() { return new uint8_t(0); });

    copy(begin(nametables), end(nametables), begin(this->memory) + NAME_0);
    copy(begin(nametables), end(nametables), begin(this->memory) + NAME_MIRRORING_STARTS);
}

void VRam::generatePaletteRam()
{
    uint8_t* paletteRam[NAME_SIZE * 4] = {};
    generate(begin(paletteRam), end(paletteRam), []() { return new uint8_t(0); });

    for (auto i = 0; i < PALETTE_TOTAL + 1; ++i)
        copy(begin(paletteRam), end(paletteRam), begin(this->memory) + PALETTE_STARTS + (PALETTE_SIZE * i) );
}