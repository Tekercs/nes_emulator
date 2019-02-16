#pragma once

#include <cstdint>

#define STACK_POINTER 0x0100

#define FLAGMASK_CARRY     0B00000001
#define FLAGMASK_ZERO      0B00000010
#define FLAGMASK_INTERRUPT 0B00000100
#define FLAGMASK_DECMODE   0B00001000
#define FLAGMASK_BREAK     0B00010000
#define FLAGMASK_OVERFLOW  0B01000000
#define FLAGMASK_NEGATIVE  0B10000000

namespace Emulator::Cpu
{
    class Cpu
    {
    private:
        uint16_t programCounter;
        uint8_t stackPointerOffset;
        uint8_t accumulator;
        uint8_t indexRegisterX;
        uint8_t indexRegisterY;
        uint8_t processorStatus;

    public:
        Cpu();

    };
}