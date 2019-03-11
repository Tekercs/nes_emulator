#pragma once

#include <cstdint>

#define VRAM_SIZE 0x4000
#define OAM_SIZE 256 

#define PATTERN_0 0x0000
#define PATTERN_1 0x1000
#define PATTERN_SIZE 0x1000

#define NAME_0 0x2000
#define NAME_1 0x2400
#define NAME_2 0x2400
#define NAME_3 0x2C00

#define NAME_SIZE 0x0400
#define NAME_MIRRORING_STARTS 0x3000

#define PALETTE_STARTS 0x3F00
#define PALETTE_SIZE 0x20
#define PALETTE_TOTAL 8

namespace Emulator::Ppu
{
    class VRam
    {
    private:
        uint8_t* memory[VRAM_SIZE];
        uint8_t* oam[OAM_SIZE];

        void generateNametable();
        void generatePaletteRam();

    public: 
        VRam();

        uint8_t readOAM(uint8_t address);
        void writeOAM(uint8_t address, uint8_t value);

        uint8_t readMemory(uint16_t address);
        void writeMemory(uint16_t address, uint8_t value);
    };

    struct OAMAccessor
    {
        uint8_t adress;
        uint8_t value;
    };
}