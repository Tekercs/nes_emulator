#include "cpu.h"

Emulator::Cpu::Cpu::Cpu()
{
    this->accumulator = 0;
    this->indexRegisterX = 0;
    this->indexRegisterY = 0;
    this->processorStatus = 0;
    this->programCounter = 0;
    this->stackPointerOffset = 0;
}
