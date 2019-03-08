#include "VRam.h"

#include <algorithm>
#include <iterator>

using namespace std;
using namespace Emulator::Ppu;

VRam::VRam()
{
    generate(begin(this->memory), end(this->memory), []() { return 0; });
    generate(begin(this->oam), end(this->oam), []() { return 0; });
}