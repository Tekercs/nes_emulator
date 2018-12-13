#pragma once
#include <cstdint>

#define MEMORY_SIZE         0x10000
#define ZEROPAGE            0x0000
#define STACK               0x0100
#define RAM                 0x0200
#define RAM_MIRROR          0x0800

#define IO_REGISTERS        0x2000
#define IO_REGISTERS_MIRROR 0x2008
#define IO_REGISTERS_SEC    0x4000

#define EXP_ROM             0x4020
#define SRAM                0x6000
#define PRG_LOWER           0x8000
#define PRG_UPPER           0xC000

namespace Emulator
{
    class Memory
    {
    private:
        uint8_t* memory[MEMORY_SIZE];

    public:
        Memory();

        void setAt(uint16_t address, uint8_t value);
        uint8_t getFrom(uint16_t address);
    };
}
