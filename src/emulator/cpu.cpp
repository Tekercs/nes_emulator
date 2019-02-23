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
    this->instructions[0x18] = [&]() { this->CLC(); };
    this->instructions[0xD8] = [&]() { this->CLD(); };
    this->instructions[0x58] = [&]() { this->CLI(); };
    this->instructions[0xB8] = [&]() { this->CLV(); };
    this->instructions[0xA9] = [&]() { this->LDA(this->immediateAddressing()); };
    this->instructions[0xA5] = [&]() { this->LDA(this->zeroPageValueAddressing()); };
    this->instructions[0xB5] = [&]() { this->LDA(this->zeroPageXValueAddressing()); };
    this->instructions[0xAD] = [&]() { this->LDA(this->absoluteValueAddressing()); };
    this->instructions[0xBD] = [&]() { this->LDA(this->absoluteXValueAddressing()); };
    this->instructions[0xB9] = [&]() { this->LDA(this->absoluteYValueAddressing()); };
    this->instructions[0x4C] = [&]() { this->JMP(this->absoluteLocationAddressing()); };
    this->instructions[0x69] = [&]() { this->ADC(this->immediateAddressing()); };
    this->instructions[0x65] = [&]() { this->ADC(this->zeroPageValueAddressing()); };
    this->instructions[0x75] = [&]() { this->ADC(this->zeroPageXValueAddressing()); };
    this->instructions[0x6D] = [&]() { this->ADC(this->absoluteValueAddressing()); };
    this->instructions[0x7D] = [&]() { this->ADC(this->absoluteXValueAddressing()); };
    this->instructions[0x79] = [&]() { this->ADC(this->absoluteYValueAddressing()); };
    this->instructions[0xE9] = [&]() { this->SBC(this->immediateAddressing()); };
    this->instructions[0xE5] = [&]() { this->SBC(this->zeroPageValueAddressing()); };
    this->instructions[0xF5] = [&]() { this->SBC(this->zeroPageXValueAddressing()); };
    this->instructions[0xED] = [&]() { this->SBC(this->absoluteValueAddressing()); };
    this->instructions[0xFD] = [&]() { this->SBC(this->absoluteXValueAddressing()); };
    this->instructions[0xF9] = [&]() { this->SBC(this->absoluteYValueAddressing()); };
    this->instructions[0x85] = [&]() { this->STA(this->zeroPageAddressing()); };
    this->instructions[0x95] = [&]() { this->STA(this->zeroPageXAddressing()); };
    this->instructions[0x8D] = [&]() { this->STA(this->absoluteLocationAddressing()); };
    this->instructions[0x9D] = [&]() { this->STA(this->absoluteYLocationAddressing()); };
    this->instructions[0x99] = [&]() { this->STA(this->absoluteYLocationAddressing()); };
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
    ++this->programCounter;
}

void Cpu::PLP()
{
    this->statusFlags = this->pullStack();
    ++this->programCounter;
}

void Cpu::SEC()
{
    this->setCarryRemain(true);
    ++this->programCounter;
}

void Cpu::SED()
{
    this->setDecimalModeOn(true);
    ++this->programCounter;
}

void Cpu::SEI()
{
    this->setInterruptsDisabled(true);
    ++this->programCounter;
}

void Cpu::CLC()
{
    this->setCarryRemain(false);
    ++this->programCounter;
}

void Cpu::CLD()
{
    this->setCarryRemain(false);
    ++this->programCounter;
}

void Cpu::CLI()
{
    this->setInterruptsDisabled(false);
    ++this->programCounter;
}

void Cpu::CLV()
{
    this->setOverflowHappened(false);
    ++this->programCounter;
}

void Cpu::LDA(uint8_t value)
{
    this->accumulator = value;

    this->setZeroResult(this->accumulator == 0);
    this->setZeroResult((this->accumulator & 0B10000000) != 0);

    ++this->programCounter;
}

void Cpu::JMP(uint16_t address)
{
    this->programCounter = address;
}

void Cpu::ADC(uint8_t value)
{
    uint32_t result = this->accumulator + value + this->isCarryRemain();

    if (result > 0xFF)
        this->setCarryRemain(true);

    this->setZeroResult(result == 0);
    this->setOverflowHappened(~(this->accumulator ^ value) & (this->accumulator ^ result) & 0B10000000);

    this->accumulator = static_cast<uint8_t>(result);

    ++this->programCounter;
}

void Cpu::SBC(uint8_t value)
{
    this->ADC(~(value));
}

void Cpu::STA(uint16_t address)
{
    this->memory->setAt(address, this->accumulator);
    ++this->programCounter;
}

uint8_t Cpu::immediateAddressing()
{
    this->programCounter++;
    return this->memory->getFrom(this->programCounter);
}

uint8_t Cpu::zeroPageAddressing()
{
    this->programCounter++;
    return this->memory->getFrom(this->programCounter);
}

uint8_t Cpu::zeroPageXAddressing()
{
    this->programCounter++;
    uint8_t zeroPageAddress = this->memory->getFrom(this->programCounter);

    return zeroPageAddress + this->indexRegisterX;
}

uint8_t Cpu::zeroPageValueAddressing()
{
    return this->memory->getFrom(this->zeroPageAddressing());
}

uint8_t Cpu::zeroPageXValueAddressing()
{
    return this->memory->getFrom(this->zeroPageXAddressing());
}

uint8_t Cpu::absoluteValueAddressing()
{
    return this->memory->getFrom(this->absoluteLocationAddressing());
}

uint8_t Cpu::absoluteXValueAddressing()
{
    return this->memory->getFrom(this->absoluteXLocationAddressing());
}

uint8_t Cpu::absoluteYValueAddressing()
{
    return this->memory->getFrom(this->absoluteYLocationAddressing());
}

uint16_t Cpu::absoluteLocationAddressing()
{
    uint16_t address = 0x0000;

    this->programCounter++;
    uint16_t addressLeastSignificant = 0x0000 + this->memory->getFrom(this->programCounter);

    this->programCounter++;
    uint16_t addressMostSingicant = 0x0000 + this->memory->getFrom(this->programCounter);

    address = (addressMostSingicant << 8) + addressLeastSignificant;

    return address;
}

uint16_t Cpu::absoluteXLocationAddressing()
{
    return this->absoluteLocationAddressing() + this->indexRegisterX;
}

uint16_t Cpu::absoluteYLocationAddressing()
{
    return this->absoluteLocationAddressing() + this->indexRegisterY;
}

void Cpu::operator++()
{
    uint8_t opcode = this->memory->getFrom(this->programCounter);
    (this->instructions[opcode])();
}
