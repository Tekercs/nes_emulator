#pragma once

#include <cstdint>

#define VRAM_SIZE 0x10000
#define OAM_SIZE  0x10000

#define PATTERN_0 0x0000
#define PATTERN_1 0x1000
#define PATTERN_SIZE 0x1000

#define NAME_0 0x2000
#define NAME_1 0x2400
#define NAME_2 0x2400
#define NAME_3 0x2C00

#define NAME_SIZE 0x0400
#define NAME_MIRRORING_STARTS 0x3000

namespace Emulator::Ppu
{
    class VRam
    {
    private:
        uint8_t* memory[VRAM_SIZE];
        uint8_t oam[OAM_SIZE];

        void generateNametable();

    public: 
        VRam();
    };
}