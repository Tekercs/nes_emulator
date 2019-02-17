#include "cpu.h"

#include <utility>
#include <memory>

using namespace std;
using namespace Emulator::Cpu;

Cpu::Cpu(std::shared_ptr<Emulator::Memory::Memory> memory) : memory(move(memory))
, accumulator(INITVAL_ACCUMULATOR)
, indexRegisterX(INITVAL_INDEXREGISTERX)
, indexRegisterY(INITVAL_INDEXREGISTERY)
, statusFlags(INITVAL_STATUSFLAGS)
, programCounter(INITVAL_PROGRAMCOUNTER)
, stackPointerOffset(INITVAL_STACKPOINTEROFFSET)
{}

bool Cpu::isCarryRemain() const
{
    return (this->statusFlags & FLAGMASK_CARRY) != 0;
}

bool Cpu::isZeroResult() const
{
    return (this->statusFlags & FLAGMASK_ZERO) != 0;
}

bool Cpu::isInterruptsDisabled() const
{
    return (this->statusFlags & FLAGMASK_INTERRUPT) != 0;
}

bool Cpu::isDecimalModeOn() const
{
    return (this->statusFlags & FLAGMASK_DECMODE) != 0;
}

bool Cpu::isBreakExecuted() const
{
    return (this->statusFlags & FLAGMASK_BREAK) != 0;
}

bool Cpu::isNegativeFlagSet() const
{
    return (this->statusFlags & FLAGMASK_NEGATIVE) != 0;
}

bool Cpu::isOverflowHappened() const
{
    return (this->statusFlags & FLAGMASK_OVERFLOW) != 0;
}

uint8_t Cpu::pullStack()
{
    ++this->stackPointerOffset;
    uint16_t stackPointer = STACK_POINTER + this->stackPointerOffset;

    return this->memory->getFrom(stackPointer);
}

void Cpu::pushStack(uint8_t value)
{
    uint16_t stackPointer = STACK_POINTER + this->stackPointerOffset;
    --this->stackPointerOffset;

    this->memory->setAt(stackPointer, value);
}
