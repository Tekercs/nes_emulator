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
    this->instructions[0xB0] = [&]() { this->BCS(this->immediateAddressing()); };
    this->instructions[0xF0] = [&]() { this->BEQ(this->immediateAddressing()); };
    this->instructions[0x24] = [&]() { this->BIT(this->zeroPageValueAddressing()); };
    this->instructions[0x2C] = [&]() { this->BIT(this->absoluteValueAddressing()); };
    this->instructions[0x30] = [&]() { this->BMI(this->immediateAddressing()); };
    this->instructions[0xD0] = [&]() { this->BNE(this->immediateAddressing()); };
    this->instructions[0x10] = [&]() { this->BPL(this->immediateAddressing()); };
    this->instructions[0x50] = [&]() { this->BVC(this->immediateAddressing()); };
    this->instructions[0x70] = [&]() { this->BVS(this->immediateAddressing()); };
    this->instructions[0xC6] = [&]() { this->DEC(this->zeroPageAddressing()); };
    this->instructions[0xD6] = [&]() { this->DEC(this->zeroPageXAddressing()); };
    this->instructions[0xCE] = [&]() { this->DEC(this->absoluteLocationAddressing()); };
    this->instructions[0xDE] = [&]() { this->DEC(this->absoluteXLocationAddressing()); };
    this->instructions[0xCA] = [&]() { this->DEX(); };
    this->instructions[0x88] = [&]() { this->DEY(); };
    this->instructions[0xE6] = [&]() { this->INC(this->zeroPageAddressing()); };
    this->instructions[0xF6] = [&]() { this->INC(this->zeroPageXAddressing()); };
    this->instructions[0xEE] = [&]() { this->INC(this->absoluteLocationAddressing()); };
    this->instructions[0xFE] = [&]() { this->INC(this->absoluteXLocationAddressing()); };
    this->instructions[0xE8] = [&]() { this->INX(); };
    this->instructions[0xC8] = [&]() { this->INY(); };
    this->instructions[0xA9] = [&]() { this->LDA(this->immediateAddressing()); };
    this->instructions[0xA5] = [&]() { this->LDA(this->zeroPageValueAddressing()); };
    this->instructions[0xB5] = [&]() { this->LDA(this->zeroPageXValueAddressing()); };
    this->instructions[0xAD] = [&]() { this->LDA(this->absoluteValueAddressing()); };
    this->instructions[0xBD] = [&]() { this->LDA(this->absoluteXValueAddressing()); };
    this->instructions[0xB9] = [&]() { this->LDA(this->absoluteYValueAddressing()); };
    this->instructions[0xA1] = [&]() { this->LDA(this->indexedIndirectValue()); };
    this->instructions[0xB1] = [&]() { this->LDA(this->indirectIndexedValue()); };
    this->instructions[0xA2] = [&]() { this->LDX(this->immediateAddressing()); };
    this->instructions[0xA6] = [&]() { this->LDX(this->zeroPageValueAddressing()); };
    this->instructions[0xB6] = [&]() { this->LDX(this->zeroPageYValueAddressing()); };
    this->instructions[0xAE] = [&]() { this->LDX(this->absoluteValueAddressing()); };
    this->instructions[0xBE] = [&]() { this->LDX(this->absoluteYValueAddressing()); };
    this->instructions[0xA0] = [&]() { this->LDY(this->immediateAddressing()); };
    this->instructions[0xA4] = [&]() { this->LDY(this->zeroPageValueAddressing()); };
    this->instructions[0xB4] = [&]() { this->LDY(this->zeroPageXValueAddressing()); };
    this->instructions[0xAC] = [&]() { this->LDY(this->absoluteValueAddressing()); };
    this->instructions[0xBC] = [&]() { this->LDY(this->absoluteXValueAddressing()); };
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
    this->instructions[0xAA] = [&]() { this->TAX(); };
    this->instructions[0xA8] = [&]() { this->TAY(); };
    this->instructions[0xBA] = [&]() { this->TSX(); };
    this->instructions[0x8A] = [&]() { this->TXA(); };
    this->instructions[0x9A] = [&]() { this->TXS(); };
    this->instructions[0x98] = [&]() { this->TYA(); };
    this->instructions[0x4C] = [&]() { this->JMP(this->absoluteLocationAddressing()); };
    this->instructions[0x6C] = [&]() { this->JMP(this->indirectAddress()); };
    this->instructions[0xE9] = [&]() { this->SBC(this->immediateAddressing()); };
    this->instructions[0xE5] = [&]() { this->SBC(this->zeroPageValueAddressing()); };
    this->instructions[0xF5] = [&]() { this->SBC(this->zeroPageXValueAddressing()); };
    this->instructions[0xED] = [&]() { this->SBC(this->absoluteValueAddressing()); };
    this->instructions[0xFD] = [&]() { this->SBC(this->absoluteXValueAddressing()); };
    this->instructions[0xF9] = [&]() { this->SBC(this->absoluteYValueAddressing()); };
    this->instructions[0xE1] = [&]() { this->SBC(this->indexedIndirectValue()); };
    this->instructions[0xF1] = [&]() { this->SBC(this->indirectIndexedValue()); };
    this->instructions[0x85] = [&]() { this->STA(this->zeroPageAddressing()); };
    this->instructions[0x95] = [&]() { this->STA(this->zeroPageXAddressing()); };
    this->instructions[0x8D] = [&]() { this->STA(this->absoluteLocationAddressing()); };
    this->instructions[0x9D] = [&]() { this->STA(this->absoluteYLocationAddressing()); };
    this->instructions[0x99] = [&]() { this->STA(this->absoluteYLocationAddressing()); };
    this->instructions[0x81] = [&]() { this->STA(this->indexedIndirectAddress()); };
    this->instructions[0x91] = [&]() { this->STA(this->indirectIndexedAddress()); };
    this->instructions[0x86] = [&]() { this->STX(this->zeroPageAddressing()); };
    this->instructions[0x96] = [&]() { this->STX(this->zeroPageYAddressing()); };
    this->instructions[0x8E] = [&]() { this->STX(this->absoluteLocationAddressing()); };
    this->instructions[0x84] = [&]() { this->STY(this->zeroPageAddressing()); };
    this->instructions[0x94] = [&]() { this->STY(this->zeroPageXAddressing()); };
    this->instructions[0x8C] = [&]() { this->STY(this->absoluteLocationAddressing()); };
    this->instructions[0xEA] = [&]() { this->NOP(); };
    this->instructions[0x2A] = [&]() { this->ROLAccumulator(); };
    this->instructions[0x26] = [&]() { this->ROL(this->zeroPageAddressing()); };
    this->instructions[0x36] = [&]() { this->ROL(this->zeroPageXAddressing()); };
    this->instructions[0x2E] = [&]() { this->ROL(this->absoluteLocationAddressing()); };
    this->instructions[0x3E] = [&]() { this->ROL(this->absoluteXLocationAddressing()); };
    this->instructions[0x6A] = [&]() { this->RORAccumulator(); };
    this->instructions[0x66] = [&]() { this->ROR(this->zeroPageAddressing()); };
    this->instructions[0x76] = [&]() { this->ROR(this->zeroPageXAddressing()); };
    this->instructions[0x6E] = [&]() { this->ROR(this->absoluteLocationAddressing()); };
    this->instructions[0x7E] = [&]() { this->ROR(this->absoluteXLocationAddressing()); };
    this->instructions[0x4A] = [&]() { this->LSRAccumulator(); };
    this->instructions[0x46] = [&]() { this->LSR(this->zeroPageAddressing()); };
    this->instructions[0x56] = [&]() { this->LSR(this->zeroPageXAddressing()); };
    this->instructions[0x4E] = [&]() { this->LSR(this->absoluteLocationAddressing()); };
    this->instructions[0x5E] = [&]() { this->LSR(this->absoluteXLocationAddressing()); };
    this->instructions[0xC9] = [&]() { this->CMP(this->immediateAddressing()); };
    this->instructions[0xC5] = [&]() { this->CMP(this->zeroPageValueAddressing()); };
    this->instructions[0xD5] = [&]() { this->CMP(this->zeroPageXValueAddressing()); };
    this->instructions[0xCD] = [&]() { this->CMP(this->absoluteValueAddressing()); };
    this->instructions[0xDD] = [&]() { this->CMP(this->absoluteXValueAddressing()); };
    this->instructions[0xD9] = [&]() { this->CMP(this->absoluteYValueAddressing()); };
    this->instructions[0xC1] = [&]() { this->CMP(this->indexedIndirectValue()); };
    this->instructions[0xD1] = [&]() { this->CMP(this->indirectIndexedValue()); };
    this->instructions[0xE0] = [&]() { this->CPX(this->immediateAddressing()); };
    this->instructions[0xE4] = [&]() { this->CPX(this->zeroPageValueAddressing()); };
    this->instructions[0xEC] = [&]() { this->CPX(this->absoluteValueAddressing()); };
    this->instructions[0xC0] = [&]() { this->CPY(this->immediateAddressing()); };
    this->instructions[0xC4] = [&]() { this->CPY(this->zeroPageValueAddressing()); };
    this->instructions[0xCC] = [&]() { this->CPY(this->absoluteValueAddressing()); };
    this->instructions[0x49] = [&]() { this->EOR(this->immediateAddressing()); };
    this->instructions[0x45] = [&]() { this->EOR(this->zeroPageValueAddressing()); };
    this->instructions[0x55] = [&]() { this->EOR(this->zeroPageXValueAddressing()); };
    this->instructions[0x4D] = [&]() { this->EOR(this->absoluteValueAddressing()); };
    this->instructions[0x5D] = [&]() { this->EOR(this->absoluteXValueAddressing()); };
    this->instructions[0x59] = [&]() { this->EOR(this->absoluteYValueAddressing()); };
    this->instructions[0x41] = [&]() { this->EOR(this->indexedIndirectValue()); };
    this->instructions[0x51] = [&]() { this->EOR(this->indirectIndexedValue()); };
    this->instructions[0x09] = [&]() { this->ORA(this->immediateAddressing()); };
    this->instructions[0x05] = [&]() { this->ORA(this->zeroPageValueAddressing()); };
    this->instructions[0x15] = [&]() { this->ORA(this->zeroPageXValueAddressing()); };
    this->instructions[0x0D] = [&]() { this->ORA(this->absoluteValueAddressing()); };
    this->instructions[0x5D] = [&]() { this->ORA(this->absoluteXValueAddressing()); };
    this->instructions[0x1D] = [&]() { this->ORA(this->absoluteYValueAddressing()); };
    this->instructions[0x01] = [&]() { this->ORA(this->indexedIndirectValue()); };
    this->instructions[0x11] = [&]() { this->ORA(this->indirectIndexedValue()); };
    this->instructions[0x20] = [&]() { this->JSR(this->absoluteLocationAddressing()); };
    this->instructions[0x60] = [&]() { this->RTS(); };
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

void Cpu::LDX(uint8_t value)
{
    this->indexRegisterX = value;

    this->setZeroResult(this->indexRegisterX == 0);
    this->setZeroResult((this->indexRegisterX & 0B10000000) != 0);

    ++this->programCounter;
}

void Cpu::LDY(uint8_t value)
{
    this->indexRegisterY = value;

    this->setZeroResult(this->indexRegisterY == 0);
    this->setZeroResult((this->indexRegisterY & 0B10000000) != 0);

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

void Cpu::BCS(int8_t value)
{
    if (this->isCarryRemain())
        this->programCounter += value;

    ++this->programCounter;
}

void Cpu::BEQ(int8_t value)
{
    if (this->isZeroResult())
        this->programCounter += value;

    ++this->programCounter;
}

void Cpu::BMI(int8_t value)
{
    if (this->isNegativeFlagSet())
        this->programCounter += value;

    ++this->programCounter;
}

void Cpu::BNE(int8_t value)
{
    if (!this->isZeroResult())
        this->programCounter += value;

    ++this->programCounter;
}

void Cpu::BPL(int8_t value)
{
    if (!this->isNegativeFlagSet())
        this->programCounter += value;

    ++this->programCounter;
}

void Cpu::BVC(int8_t value)
{
    if (!this->isOverflowHappened())
        this->programCounter += value;

    ++this->programCounter;
}

void Cpu::BVS(int8_t value)
{
    if (this->isOverflowHappened())
        this->programCounter += value;

    ++this->programCounter;
}

void Cpu::BIT(uint8_t value)
{
    uint8_t result = this->accumulator & value;

    this->setNegativeFlagSet((result & 0B10000000));
    this->setOverflowHappened((result & 0B01000000));
    this->setZeroResult(result == 0);

    ++this->programCounter;
}

void Cpu::DEC(uint16_t address)
{
    uint8_t value = this->memory->getFrom(address);
    --value;

    this->setZeroResult(value == 0);
    this->setNegativeFlagSet(value & 0B10000000);

    this->memory->setAt(address, value);

    ++this->programCounter;
}

void Cpu::INC(uint16_t address)
{
    uint8_t value = this->memory->getFrom(address);
    ++value;

    this->setZeroResult(value == 0);
    this->setNegativeFlagSet(value & 0B10000000);

    this->memory->setAt(address, value);

    ++this->programCounter;
}

void Cpu::DEX()
{
    --this->indexRegisterX;

    this->setZeroResult(this->indexRegisterX == 0);
    this->setNegativeFlagSet(this->indexRegisterX & 0B10000000);

    ++this->programCounter;
}

void Cpu::INX()
{
    ++this->indexRegisterX;

    this->setZeroResult(this->indexRegisterX == 0);
    this->setNegativeFlagSet(this->indexRegisterX & 0B10000000);

    ++this->programCounter;
}

void Cpu::DEY()
{
    --this->indexRegisterY;

    this->setZeroResult(this->indexRegisterY == 0);
    this->setNegativeFlagSet(this->indexRegisterY & 0B10000000);

    ++this->programCounter;
}

void Cpu::INY()
{
    ++this->indexRegisterY;

    this->setZeroResult(this->indexRegisterY == 0);
    this->setNegativeFlagSet(this->indexRegisterY & 0B10000000);

    ++this->programCounter;
}

void Cpu::ROLAccumulator()
{
    uint16_t newValue = this->accumulator;
    newValue = newValue << 1;

    if (this->isCarryRemain())
        ++newValue;

    this->setCarryRemain(newValue & 0B100000000);
    this->accumulator = newValue;

    this->setNegativeFlagSet(this->accumulator & 0B10000000);
    this->setZeroResult(this->accumulator == 0);

    ++this->programCounter;
}

void Cpu::ROL(uint16_t address)
{
    uint16_t newValue = this->memory->getFrom(address);
    newValue = newValue << 1;

    if (this->isCarryRemain())
        ++newValue;

    this->setCarryRemain(newValue & 0B100000000);
    this->memory->setAt(address, newValue);

    this->setNegativeFlagSet(newValue & 0B10000000);
    this->setZeroResult(newValue == 0);

    ++this->programCounter;
}

void Cpu::RORAccumulator()
{
    uint16_t newValue = (this->isCarryRemain()) ? 1 << 8 : 0;
    newValue += this->accumulator;

    this->setCarryRemain(newValue & 0b1);

    newValue = newValue >> 1;
    this->accumulator = newValue;

    this->setZeroResult(this->accumulator == 0);
    this->setNegativeFlagSet(newValue & 0B10000000);

    ++this->programCounter;
}

void Cpu::ROR(uint16_t address)
{
    uint16_t newValue = (this->isCarryRemain()) ? 1 << 8 : 0;
    newValue += this->memory->getFrom(address);

    this->setCarryRemain(newValue & 0b1);

    newValue = newValue >> 1;
    this->memory->setAt(address, newValue);

    this->setNegativeFlagSet(newValue & 0B10000000);
    this->setZeroResult(newValue == 0);

    ++this->programCounter;
}

void Cpu::LSRAccumulator()
{
    uint8_t newValue = this->accumulator;

    this->setCarryRemain(newValue & 0b1);

    newValue = newValue >> 1;
    this->accumulator = newValue;

    this->setZeroResult(this->accumulator == 0);
    this->setNegativeFlagSet(newValue & 0B10000000);

    ++this->programCounter;
}

void Cpu::LSR(uint16_t address)
{
    uint8_t newValue = this->memory->getFrom(address);

    this->setCarryRemain(newValue & 0b1);

    newValue = newValue >> 1;
    this->memory->setAt(address, newValue);

    this->setNegativeFlagSet(newValue & 0B10000000);
    this->setZeroResult(newValue == 0);

    ++this->programCounter;
}

void Cpu::CMP(uint8_t value)
{
    this->setCarryRemain(this->accumulator >= value);
    this->setZeroResult(this->accumulator == value);

    this->setNegativeFlagSet((this->accumulator - value) & 0B10000000);

    ++this->programCounter;
}

void Cpu::CPX(uint8_t value)
{
    this->setCarryRemain(this->indexRegisterX >= value);
    this->setZeroResult(this->indexRegisterX == value);

    this->setNegativeFlagSet((this->indexRegisterX - value) & 0B10000000);

    ++this->programCounter;
}

void Cpu::CPY(uint8_t value)
{
    this->setCarryRemain(this->indexRegisterY >= value);
    this->setZeroResult(this->indexRegisterY == value);

    this->setNegativeFlagSet((this->indexRegisterY - value) & 0B10000000);

    ++this->programCounter;
}

void Cpu::EOR(uint8_t value)
{
    this->accumulator = this->accumulator ^ value;

    this->setZeroResult(this->accumulator == 0);
    this->setNegativeFlagSet((this->accumulator & 0B10000000) > 0);

    ++this->programCounter;
}

void Cpu::ORA(uint8_t value)
{
    this->accumulator = this->accumulator | value;

    this->setZeroResult(this->accumulator == 0);
    this->setNegativeFlagSet((this->accumulator & 0B10000000) > 0);

    ++this->programCounter;
}

void Cpu::JSR(uint16_t address)
{
    uint8_t highByte = this->programCounter >> 8;
    uint8_t lowByte = this->programCounter;

    this->pushStack(highByte);
    this->pushStack(lowByte);

    this->programCounter = address;
}

void Cpu::RTS()
{
    uint8_t lowByte = this->pullStack();
    uint8_t highByte = this->pullStack();

    this->programCounter = highByte << 8;
    this->programCounter += lowByte;

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

uint8_t Cpu::zeroPageYValueAddressing()
{
    return this->memory->getFrom(this->zeroPageYAddressing());
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

uint16_t Cpu::indirectAddress()
{
    uint16_t address = 0x0000;

    ++this->programCounter;
    uint16_t addressLeastSignificant = 0x0000 + this->memory->getFrom(this->programCounter);

    ++this->programCounter;
    uint16_t addressMostSingicant = 0x0000 + this->memory->getFrom(this->programCounter);

    address = (addressMostSingicant << 8) + addressLeastSignificant;

    addressLeastSignificant = 0x0000 + this->memory->getFrom(address);
    ++address;
    addressMostSingicant = 0x0000 + this->memory->getFrom(address);

    address = (addressMostSingicant << 8) + addressLeastSignificant;

    return address;

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

    uint16_t address = 0x0000;
    uint16_t addressLeastSignificant = 0x0000 + this->memory->getFrom(zeroPageAddress);

    ++zeroPageAddress;
    uint16_t addressMostSingicant = 0x0000 + this->memory->getFrom(zeroPageAddress);

    address = (addressMostSingicant << 8) + addressLeastSignificant;
    address += this->indexRegisterY;

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
