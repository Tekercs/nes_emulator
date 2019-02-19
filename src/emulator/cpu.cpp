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
{
    this->initInstructionMap();
}

bool Cpu::checkFlagBit(uint8_t flagBit) const
{
    return (this->statusFlags & (0x01 << flagBit)) != 0;
}

bool Cpu::isCarryRemain() const
{
    return this->checkFlagBit(FLAGBIT_CARRY);
}

bool Cpu::isZeroResult() const
{
    return this->checkFlagBit(FLAGBIT_ZERO);
}

bool Cpu::isInterruptsDisabled() const
{
    return this->checkFlagBit(FLAGBIT_INTERRUPT);
}

bool Cpu::isDecimalModeOn() const
{
    return this->checkFlagBit(FLAGBIT_DECMODE);
}

bool Cpu::isBreakExecuted() const
{
    return this->checkFlagBit(FLAGBIT_BREAK);
}

bool Cpu::isNegativeFlagSet() const
{
    return this->checkFlagBit(FLAGBIT_NEGATIVE);
}

bool Cpu::isOverflowHappened() const
{
    return this->checkFlagBit(FLAGBIT_OVERFLOW);
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

void Cpu::initInstructionMap()
{
    this->instructions[0x48] = [&]() { this->PHA(); };
    this->instructions[0x68] = [&]() { this->PLA(); };
    this->instructions[0x08] = [&]() { this->PHP(); };
    this->instructions[0x28] = [&]() { this->PLP(); };
    this->instructions[0x38] = [&]() { this->SEC(); };
    this->instructions[0xF8] = [&]() { this->SED(); };
    this->instructions[0x78] = [&]() { this->SEI(); };
}

void Cpu::setFlagBit(uint8_t flagBit, bool value)
{
    this->statusFlags ^= (-(uint8_t)value ^ this->statusFlags) & (0x01 << flagBit);
}

void Cpu::setCarryRemain(bool value)
{
    this->setFlagBit(FLAGBIT_CARRY, value);
}

void Cpu::setZeroResult(bool value)
{
    this->setFlagBit(FLAGBIT_ZERO, value);
}

void Cpu::setInterruptsDisabled(bool value)
{
    this->setFlagBit(FLAGBIT_INTERRUPT, value);
}

void Cpu::setDecimalModeOn(bool value)
{
    this->setFlagBit(FLAGBIT_DECMODE, value);
}

void Cpu::setBreakExecuted(bool value)
{
    this->setFlagBit(FLAGBIT_BREAK, value);
}

void Cpu::setOverflowHappened(bool value)
{
    this->setFlagBit(FLAGBIT_OVERFLOW, value);
}

void Cpu::setNegativeFlagSet(bool value)
{
    this->setFlagBit(FLAGBIT_NEGATIVE, value);
}

void Cpu::PHA()
{
    this->pushStack(this->accumulator);
}

void Cpu::PLA()
{
    this->accumulator = this->pullStack();

    this->setZeroResult(this->accumulator == 0);
    this->setZeroResult((this->accumulator & 0B10000000) != 0);
}

void Cpu::PHP()
{
    this->pushStack(this->statusFlags);
}

void Cpu::PLP()
{
    this->statusFlags = this->pullStack();
}

void Cpu::SEC()
{
    this->setCarryRemain(true);
}

void Cpu::SED()
{
    this->setDecimalModeOn(true);
}

void Cpu::SEI()
{
    this->setInterruptsDisabled(true);
}
