#pragma once

#include <cstdint>

#define VRAM_SIZE 0x10000
#define OAM_SIZE  0x10000

namespace Emulator::Ppu
{
    class VRam
    {
    private:
        uint8_t memory[VRAM_SIZE];
        uint8_t oam[OAM_SIZE];

    public: 
        VRam();
    };
}