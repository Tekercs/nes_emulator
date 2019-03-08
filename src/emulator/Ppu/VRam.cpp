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
}

void VRam::generateNametable()
{
    uint8_t* nametables[NAME_SIZE * 4] = {};
    generate(begin(nametables), end(nametables), []() { return new uint8_t(0); });

    copy(begin(nametables), end(nametables), begin(this->memory) + NAME_0);
    copy(begin(nametables), end(nametables), begin(this->memory) + NAME_MIRRORING_STARTS);

}