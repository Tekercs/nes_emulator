#pragma once

#include <cstdint>

#define STACK_POINTER 0x0100


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