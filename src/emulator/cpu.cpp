#include "cpu.h"

Emulator::Cpu::Cpu::Cpu()
{
    this->accumulator = 0;
    this->indexRegisterX = 0;
    this->indexRegisterY = 0;
    this->statusFlags = 0;
    this->programCounter = 0;
    this->stackPointerOffset = 0;
}

bool Emulator::Cpu::Cpu::isCarryRemain() const
{
    return (this->statusFlags & FLAGMASK_CARRY) != 0;
}

bool Emulator::Cpu::Cpu::isZeroResult() const
{
    return (this->statusFlags & FLAGMASK_ZERO) != 0;
}

bool Emulator::Cpu::Cpu::isInterruptsDisabled() const
{
    return (this->statusFlags & FLAGMASK_INTERRUPT) != 0;
}

bool Emulator::Cpu::Cpu::isDecimalModeOn() const
{
    return (this->statusFlags & FLAGMASK_DECMODE) != 0;
}

bool Emulator::Cpu::Cpu::isBreakExecuted() const
{
    return (this->statusFlags & FLAGMASK_BREAK) != 0;
}

bool Emulator::Cpu::Cpu::isNegativeFlagSet() const
{
    return (this->statusFlags & FLAGMASK_NEGATIVE) != 0;
}

bool Emulator::Cpu::Cpu::isOverflowHappened() const
{
    return (this->statusFlags & FLAGMASK_OVERFLOW) != 0;
}
