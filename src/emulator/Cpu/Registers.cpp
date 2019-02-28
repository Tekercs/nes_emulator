#include "Registers.h"

using namespace Emulator::Cpu;

Registers::Registers()
: accumulator(INITVAL_ACCUMULATOR)
, indexRegisterX(INITVAL_INDEXREGISTERX)
, indexRegisterY(INITVAL_INDEXREGISTERY)
, statusFlags(INITVAL_STATUSFLAGS)
, programCounter(INITVAL_PROGRAMCOUNTER)
, stackPointerOffset(INITVAL_STACKPOINTEROFFSET)
{

}

void Registers::setFlagBit(uint8_t flagBit, bool value)
{
    this->statusFlags ^= (-(uint8_t)value ^ this->statusFlags) & (0x01 << flagBit);
}

void Registers::setCarryRemain(bool value)
{
    this->setFlagBit(FLAGBIT_CARRY, value);
}

void Registers::setZeroResult(bool value)
{
    this->setFlagBit(FLAGBIT_ZERO, value);
}

void Registers::setInterruptsDisabled(bool value)
{
    this->setFlagBit(FLAGBIT_INTERRUPT, value);
}

void Registers::setDecimalModeOn(bool value)
{
    this->setFlagBit(FLAGBIT_DECMODE, value);
}

void Registers::setBreakExecuted(bool value)
{
    this->setFlagBit(FLAGBIT_BREAK, value);
}

void Registers::setOverflowHappened(bool value)
{
    this->setFlagBit(FLAGBIT_OVERFLOW, value);
}

void Registers::setNegativeFlagSet(bool value)
{
    this->setFlagBit(FLAGBIT_NEGATIVE, value);
}

bool Registers::checkFlagBit(uint8_t flagBit) const
{
    return (this->statusFlags & (0x01 << flagBit)) != 0;
}

bool Registers::isCarryRemain() const
{
    return this->checkFlagBit(FLAGBIT_CARRY);
}

bool Registers::isZeroResult() const
{
    return this->checkFlagBit(FLAGBIT_ZERO);
}

bool Registers::isInterruptsDisabled() const
{
    return this->checkFlagBit(FLAGBIT_INTERRUPT);
}

bool Registers::isDecimalModeOn() const
{
    return this->checkFlagBit(FLAGBIT_DECMODE);
}

bool Registers::isBreakExecuted() const
{
    return this->checkFlagBit(FLAGBIT_BREAK);
}

bool Registers::isNegativeFlagSet() const
{
    return this->checkFlagBit(FLAGBIT_NEGATIVE);
}

bool Registers::isOverflowHappened() const
{
    return this->checkFlagBit(FLAGBIT_OVERFLOW);
}

uint16_t Registers::getProgramCounter() const
{
    return programCounter;
}

void Registers::setProgramCounter(uint16_t programCounter)
{
    Registers::programCounter = programCounter;
}

uint8_t Registers::getStackPointerOffset() const
{
    return stackPointerOffset;
}

void Registers::setStackPointerOffset(uint8_t stackPointerOffset)
{
    Registers::stackPointerOffset = stackPointerOffset;
}

uint8_t Registers::getAccumulator() const
{
    return accumulator;
}

void Registers::setAccumulator(uint8_t accumulator)
{
    Registers::accumulator = accumulator;
}

uint8_t Registers::getIndexRegisterX() const
{
    return indexRegisterX;
}

void Registers::setIndexRegisterX(uint8_t indexRegisterX)
{
    Registers::indexRegisterX = indexRegisterX;
}

uint8_t Registers::getIndexRegisterY() const
{
    return indexRegisterY;
}

void Registers::setIndexRegisterY(uint8_t indexRegisterY)
{
    Registers::indexRegisterY = indexRegisterY;
}

void Registers::incrementStackPointerOffset()
{
    ++this->stackPointerOffset;
}

void Registers::decrementStackPointerOffset()
{
    --this->stackPointerOffset;
}

void Registers::incrementProgramCounter()
{
    ++this->programCounter;
}

void Registers::setStatusFlags(uint8_t statusFlags)
{
    Registers::statusFlags = statusFlags;
}

uint8_t Registers::getStatusFlags() const
{
    return statusFlags;
}


