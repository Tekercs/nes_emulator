#include <utility>

#include "cpu.h"

#include <memory>

Emulator::Cpu::Cpu::Cpu(std::shared_ptr<Emulator::Memory::Memory> memory) : memory(std::move(memory))
, accumulator(INITVAL_ACCUMULATOR)
, indexRegisterX(INITVAL_INDEXREGISTERX)
, indexRegisterY(INITVAL_INDEXREGISTERY)
, statusFlags(INITVAL_STATUSFLAGS)
, programCounter(INITVAL_PROGRAMCOUNTER)
, stackPointerOffset(INITVAL_STACKPOINTEROFFSET)
{}

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

uint8_t Emulator::Cpu::Cpu::pullStack()
{
    uint16_t stackPointer = STACK_POINTER + this->stackPointerOffset;
    ++this->stackPointerOffset;

    return this->memory->getFrom(stackPointer);
}

void Emulator::Cpu::Cpu::pushStack(uint8_t value)
{
    --this->stackPointerOffset;
    uint16_t stackPointer = STACK_POINTER + this->stackPointerOffset;

    this->memory->setAt(stackPointer, value);
}
