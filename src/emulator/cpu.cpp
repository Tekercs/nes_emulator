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
    this->instructions[0x69] = [&]() { this->ADC(this->immediateAddressing()); };
    this->instructions[0x65] = [&]() { this->ADC(this->zeroPageValueAddressing()); };
    this->instructions[0x75] = [&]() { this->ADC(this->zeroPageXValueAddressing()); };
    this->instructions[0x6D] = [&]() { this->ADC(this->absoluteValueAddressing()); };
    this->instructions[0x7D] = [&]() { this->ADC(this->absoluteXValueAddressing()); };
    this->instructions[0x79] = [&]() { this->ADC(this->absoluteYValueAddressing()); };
    this->instructions[0x61] = [&]() { this->ADC(this->indexedIndirectValue()); };
    this->instructions[0x71] = [&]() { this->ADC(this->indirectIndexedValue()); };
    this->instructions[0x29] = [&]() { this->AND(this->immediateAddressing()); };
    this->instructions[0x25] = [&]() { this->AND(this->zeroPageValueAddressing()); };
    this->instructions[0x35] = [&]() { this->AND(this->zeroPageXValueAddressing()); };
    this->instructions[0x2D] = [&]() { this->AND(this->absoluteValueAddressing()); };
    this->instructions[0x3D] = [&]() { this->AND(this->absoluteXValueAddressing()); };
    this->instructions[0x39] = [&]() { this->AND(this->absoluteYValueAddressing()); };
    this->instructions[0x21] = [&]() { this->AND(this->indexedIndirectValue()); };
    this->instructions[0x31] = [&]() { this->AND(this->indirectIndexedValue()); };
    this->instructions[0x0A] = [&]() { this->ASLAccumulator(); };
    this->instructions[0x06] = [&]() { this->ASL(this->zeroPageAddressing()); };
    this->instructions[0x16] = [&]() { this->ASL(this->zeroPageXAddressing()); };
    this->instructions[0x0E] = [&]() { this->ASL(this->absoluteLocationAddressing()); };
    this->instructions[0x1E] = [&]() { this->ASL(this->absoluteXLocationAddressing()); };
    this->instructions[0x90] = [&]() { this->BCC(this->immediateAddressing()); };



    this->instructions[0xEA] = [&]() { this->NOP(); };
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
    this->instructions[0x86] = [&]() { this->STX(this->zeroPageAddressing()); };
    this->instructions[0x96] = [&]() { this->STX(this->zeroPageYAddressing()); };
    this->instructions[0x8E] = [&]() { this->STX(this->absoluteLocationAddressing()); };
    this->instructions[0x84] = [&]() { this->STY(this->zeroPageAddressing()); };
    this->instructions[0x94] = [&]() { this->STY(this->zeroPageXAddressing()); };
    this->instructions[0x8C] = [&]() { this->STY(this->absoluteLocationAddressing()); };
    this->instructions[0xAA] = [&]() { this->TAX(); };
    this->instructions[0xA8] = [&]() { this->TAY(); };
    this->instructions[0xBA] = [&]() { this->TSX(); };
    this->instructions[0x8A] = [&]() { this->TXA(); };
    this->instructions[0x9A] = [&]() { this->TXS(); };
    this->instructions[0x98] = [&]() { this->TYA(); };
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

void Cpu::STX(uint16_t address)
{
    this->memory->setAt(address, this->indexRegisterX);
    ++this->programCounter;
}

void Cpu::STY(uint16_t address)
{
    this->memory->setAt(address, this->indexRegisterY);
    ++this->programCounter;
}

void Cpu::TAX()
{
    this->indexRegisterX = this->accumulator;

    this->setZeroResult(this->indexRegisterX == 0);
    this->setNegativeFlagSet((this->indexRegisterX & 0B10000000) > 0);

    ++this->programCounter;
}

void Cpu::TAY()
{
    this->indexRegisterY = this->accumulator;

    this->setZeroResult(this->indexRegisterY == 0);
    this->setNegativeFlagSet((this->indexRegisterY & 0B10000000) > 0);

    ++this->programCounter;
}

void Cpu::TSX()
{
    this->indexRegisterX = this->stackPointerOffset;

    this->setZeroResult(this->indexRegisterX == 0);
    this->setNegativeFlagSet((this->indexRegisterX & 0B10000000) > 0);

    ++this->programCounter;
}

void Cpu::TXA()
{
    this->accumulator = this->indexRegisterX;

    this->setZeroResult(this->accumulator == 0);
    this->setNegativeFlagSet((this->accumulator & 0B10000000) > 0);

    ++this->programCounter;
}

void Cpu::TXS()
{
    this->stackPointerOffset = this->indexRegisterX;

    ++this->programCounter;
}

void Cpu::TYA()
{
    this->accumulator = this->indexRegisterY;

    this->setZeroResult(this->accumulator == 0);
    this->setNegativeFlagSet((this->accumulator & 0B10000000) > 0);

    ++this->programCounter;
}

void Cpu::AND(uint8_t value)
{
    this->accumulator = this->accumulator & value;

    this->setZeroResult(this->accumulator == 0);
    this->setNegativeFlagSet((this->accumulator & 0B10000000) > 0);

    ++this->programCounter;
}

void Cpu::NOP()
{
    ++this->programCounter;
}

void Cpu::ASL(uint16_t address)
{
    uint8_t value = this->memory->getFrom(address);
    uint16_t shiftResult = value << 1;
    value = shiftResult;

    this->setCarryRemain(shiftResult > 0xFF);
    this->setZeroResult(value == 0);
    this->setNegativeFlagSet((value & 0B10000000) > 0);

    this->memory->setAt(address, value);
    ++this->programCounter;
}

void Cpu::ASLAccumulator()
{
    uint16_t shiftResult = this->accumulator << 1;
    this->accumulator = shiftResult;

    this->setCarryRemain(shiftResult > 0xFF);
    this->setZeroResult(this->accumulator == 0);
    this->setNegativeFlagSet((this->accumulator & 0B10000000) > 0);

    ++this->programCounter;
}

void Cpu::BCC(int8_t value)
{
    if (!this->isCarryRemain())
        this->programCounter += value;

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

uint8_t Cpu::zeroPageYAddressing()
{
    this->programCounter++;
    uint8_t zeroPageAddress = this->memory->getFrom(this->programCounter);

    return zeroPageAddress + this->indexRegisterY;
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

uint16_t Cpu::indexedIndirectAddress()
{
    ++this->programCounter;
    uint8_t zeroPageAddress = this->memory->getFrom(this->programCounter);

    zeroPageAddress += this->indexRegisterX;

    uint16_t address = 0x0000;
    uint16_t addressLeastSignificant = 0x0000 + this->memory->getFrom(zeroPageAddress);

    ++zeroPageAddress;
    uint16_t addressMostSingicant = 0x0000 + this->memory->getFrom(zeroPageAddress);

    address = (addressMostSingicant << 8) + addressLeastSignificant;

    return address;
}

uint16_t Cpu::indirectIndexedAddress()
{
    ++this->programCounter;
    uint8_t zeroPageAddress = this->memory->getFrom(this->programCounter);

    zeroPageAddress += this->indexRegisterY;

    uint16_t address = 0x0000;
    uint16_t addressLeastSignificant = 0x0000 + this->memory->getFrom(zeroPageAddress);

    ++zeroPageAddress;
    uint16_t addressMostSingicant = 0x0000 + this->memory->getFrom(zeroPageAddress);

    address = (addressMostSingicant << 8) + addressLeastSignificant;

    return address;
}

uint8_t Cpu::indexedIndirectValue()
{
    return this->memory->getFrom(this->indexedIndirectAddress());
}

uint8_t Cpu::indirectIndexedValue()
{
    return this->memory->getFrom(this->indirectIndexedAddress());
}

void Cpu::operator++()
{
    uint8_t opcode = this->memory->getFrom(this->programCounter);
    (this->instructions[opcode])();
}
