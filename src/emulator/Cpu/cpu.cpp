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
{ }

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

void Cpu::executeInstruction(uint8_t opcode)
{
    switch (opcode)
    {
        case 0x69:
            this->ADC(this->immediateAddressing());
            break;
        case 0x65:
            this->ADC(this->zeroPageValueAddressing());
            break;
        case 0x75:
            this->ADC(this->zeroPageXValueAddressing());
            break;
        case 0x6D:
            this->ADC(this->absoluteValueAddressing());
            break;
        case 0x7D:
            this->ADC(this->absoluteXValueAddressing());
            break;
        case 0x79:
            this->ADC(this->absoluteYValueAddressing());
            break;
        case 0x61:
            this->ADC(this->indexedIndirectValue());
            break;
        case 0x71:
            this->ADC(this->indirectIndexedValue());
            break;
        case 0x29:
            this->AND(this->immediateAddressing());
            break;
        case 0x25:
            this->AND(this->zeroPageValueAddressing());
            break;
        case 0x35:
            this->AND(this->zeroPageXValueAddressing());
            break;
        case 0x2D:
            this->AND(this->absoluteValueAddressing());
            break;
        case 0x3D:
            this->AND(this->absoluteXValueAddressing());
            break;
        case 0x39:
            this->AND(this->absoluteYValueAddressing());
            break;
        case 0x21:
            this->AND(this->indexedIndirectValue());
            break;
        case 0x31:
            this->AND(this->indirectIndexedValue());
            break;
        case 0x0A:
            this->ASLAccumulator();
            break;
        case 0x06:
            this->ASL(this->zeroPageAddressing());
            break;
        case 0x16:
            this->ASL(this->zeroPageXAddressing());
            break;
        case 0x0E:
            this->ASL(this->absoluteLocationAddressing());
            break;
        case 0x1E:
            this->ASL(this->absoluteXLocationAddressing());
            break;
        case 0x90:
            this->BCC(this->immediateAddressing());
            break;
        case 0xB0:
            this->BCS(this->immediateAddressing());
            break;
        case 0xF0:
            this->BEQ(this->immediateAddressing());
            break;
        case 0x24:
            this->BIT(this->zeroPageValueAddressing());
            break;
        case 0x2C:
            this->BIT(this->absoluteValueAddressing());
            break;
        case 0x30:
            this->BMI(this->immediateAddressing());
            break;
        case 0xD0:
            this->BNE(this->immediateAddressing());
            break;
        case 0x10:
            this->BPL(this->immediateAddressing());
            break;
        case 0x50:
            this->BVC(this->immediateAddressing());
            break;
        case 0x70:
            this->BVS(this->immediateAddressing());
            break;
        case 0xC6:
            this->DEC(this->zeroPageAddressing());
            break;
        case 0xD6:
            this->DEC(this->zeroPageXAddressing());
            break;
        case 0xCE:
            this->DEC(this->absoluteLocationAddressing());
            break;
        case 0xDE:
            this->DEC(this->absoluteXLocationAddressing());
            break;
        case 0xCA:
            this->DEX();
            break;
        case 0x88:
            this->DEY();
            break;
        case 0xE6:
            this->INC(this->zeroPageAddressing());
            break;
        case 0xF6:
            this->INC(this->zeroPageXAddressing());
            break;
        case 0xEE:
            this->INC(this->absoluteLocationAddressing());
            break;
        case 0xFE:
            this->INC(this->absoluteXLocationAddressing());
            break;
        case 0xE8:
            this->INX();
            break;
        case 0xC8:
            this->INY();
            break;
        case 0xA9:
            this->LDA(this->immediateAddressing());
            break;
        case 0xA5:
            this->LDA(this->zeroPageValueAddressing());
            break;
        case 0xB5:
            this->LDA(this->zeroPageXValueAddressing());
            break;
        case 0xAD:
            this->LDA(this->absoluteValueAddressing());
            break;
        case 0xBD:
            this->LDA(this->absoluteXValueAddressing());
            break;
        case 0xB9:
            this->LDA(this->absoluteYValueAddressing());
            break;
        case 0xA1:
            this->LDA(this->indexedIndirectValue());
            break;
        case 0xB1:
            this->LDA(this->indirectIndexedValue());
            break;
        case 0xA2:
            this->LDX(this->immediateAddressing());
            break;
        case 0xA6:
            this->LDX(this->zeroPageValueAddressing());
            break;
        case 0xB6:
            this->LDX(this->zeroPageYValueAddressing());
            break;
        case 0xAE:
            this->LDX(this->absoluteValueAddressing());
            break;
        case 0xBE:
            this->LDX(this->absoluteYValueAddressing());
            break;
        case 0xA0:
            this->LDY(this->immediateAddressing());
            break;
        case 0xA4:
            this->LDY(this->zeroPageValueAddressing());
            break;
        case 0xB4:
            this->LDY(this->zeroPageXValueAddressing());
            break;
        case 0xAC:
            this->LDY(this->absoluteValueAddressing());
            break;
        case 0xBC:
            this->LDY(this->absoluteXValueAddressing());
            break;
        case 0x48:
            this->PHA();
            break;
        case 0x68:
            this->PLA();
            break;
        case 0x08:
            this->PHP();
            break;
        case 0x28:
            this->PLP();
            break;
        case 0x38:
            this->SEC();
            break;
        case 0xF8:
            this->SED();
            break;
        case 0x78:
            this->SEI();
            break;
        case 0x18:
            this->CLC();
            break;
        case 0xD8:
            this->CLD();
            break;
        case 0x58:
            this->CLI();
            break;
        case 0xB8:
            this->CLV();
            break;
        case 0xAA:
            this->TAX();
            break;
        case 0xA8:
            this->TAY();
            break;
        case 0xBA:
            this->TSX();
            break;
        case 0x8A:
            this->TXA();
            break;
        case 0x9A:
            this->TXS();
            break;
        case 0x98:
            this->TYA();
            break;
        case 0x4C:
            this->JMP(this->absoluteLocationAddressing());
            break;
        case 0x6C:
            this->JMP(this->indirectAddress());
            break;
        case 0xE9:
            this->SBC(this->immediateAddressing());
            break;
        case 0xE5:
            this->SBC(this->zeroPageValueAddressing());
            break;
        case 0xF5:
            this->SBC(this->zeroPageXValueAddressing());
            break;
        case 0xED:
            this->SBC(this->absoluteValueAddressing());
            break;
        case 0xFD:
            this->SBC(this->absoluteXValueAddressing());
            break;
        case 0xF9:
            this->SBC(this->absoluteYValueAddressing());
            break;
        case 0xE1:
            this->SBC(this->indexedIndirectValue());
            break;
        case 0xF1:
            this->SBC(this->indirectIndexedValue());
            break;
        case 0x85:
            this->STA(this->zeroPageAddressing());
            break;
        case 0x95:
            this->STA(this->zeroPageXAddressing());
            break;
        case 0x8D:
            this->STA(this->absoluteLocationAddressing());
            break;
        case 0x9D:
            this->STA(this->absoluteYLocationAddressing());
            break;
        case 0x99:
            this->STA(this->absoluteYLocationAddressing());
            break;
        case 0x81:
            this->STA(this->indexedIndirectAddress());
            break;
        case 0x91:
            this->STA(this->indirectIndexedAddress());
            break;
        case 0x86:
            this->STX(this->zeroPageAddressing());
            break;
        case 0x96:
            this->STX(this->zeroPageYAddressing());
            break;
        case 0x8E:
            this->STX(this->absoluteLocationAddressing());
            break;
        case 0x84:
            this->STY(this->zeroPageAddressing());
            break;
        case 0x94:
            this->STY(this->zeroPageXAddressing());
            break;
        case 0x8C:
            this->STY(this->absoluteLocationAddressing());
            break;
        case 0xEA:
            this->NOP();
            break;
        case 0x2A:
            this->ROLAccumulator();
            break;
        case 0x26:
            this->ROL(this->zeroPageAddressing());
            break;
        case 0x36:
            this->ROL(this->zeroPageXAddressing());
            break;
        case 0x2E:
            this->ROL(this->absoluteLocationAddressing());
            break;
        case 0x3E:
            this->ROL(this->absoluteXLocationAddressing());
            break;
        case 0x6A:
            this->RORAccumulator();
            break;
        case 0x66:
            this->ROR(this->zeroPageAddressing());
            break;
        case 0x76:
            this->ROR(this->zeroPageXAddressing());
            break;
        case 0x6E:
            this->ROR(this->absoluteLocationAddressing());
            break;
        case 0x7E:
            this->ROR(this->absoluteXLocationAddressing());
            break;
        case 0x4A:
            this->LSRAccumulator();
            break;
        case 0x46:
            this->LSR(this->zeroPageAddressing());
            break;
        case 0x56:
            this->LSR(this->zeroPageXAddressing());
            break;
        case 0x4E:
            this->LSR(this->absoluteLocationAddressing());
            break;
        case 0x5E:
            this->LSR(this->absoluteXLocationAddressing());
            break;
        case 0xC9:
            this->CMP(this->immediateAddressing());
            break;
        case 0xC5:
            this->CMP(this->zeroPageValueAddressing());
            break;
        case 0xD5:
            this->CMP(this->zeroPageXValueAddressing());
            break;
        case 0xCD:
            this->CMP(this->absoluteValueAddressing());
            break;
        case 0xDD:
            this->CMP(this->absoluteXValueAddressing());
            break;
        case 0xD9:
            this->CMP(this->absoluteYValueAddressing());
            break;
        case 0xC1:
            this->CMP(this->indexedIndirectValue());
            break;
        case 0xD1:
            this->CMP(this->indirectIndexedValue());
            break;
        case 0xE0:
            this->CPX(this->immediateAddressing());
            break;
        case 0xE4:
            this->CPX(this->zeroPageValueAddressing());
            break;
        case 0xEC:
            this->CPX(this->absoluteValueAddressing());
            break;
        case 0xC0:
            this->CPY(this->immediateAddressing());
            break;
        case 0xC4:
            this->CPY(this->zeroPageValueAddressing());
            break;
        case 0xCC:
            this->CPY(this->absoluteValueAddressing());
            break;
        case 0x49:
            this->EOR(this->immediateAddressing());
            break;
        case 0x45:
            this->EOR(this->zeroPageValueAddressing());
            break;
        case 0x55:
            this->EOR(this->zeroPageXValueAddressing());
            break;
        case 0x4D:
            this->EOR(this->absoluteValueAddressing());
            break;
        case 0x5D:
            this->EOR(this->absoluteXValueAddressing());
            break;
        case 0x59:
            this->EOR(this->absoluteYValueAddressing());
            break;
        case 0x41:
            this->EOR(this->indexedIndirectValue());
            break;
        case 0x51:
            this->EOR(this->indirectIndexedValue());
            break;
        case 0x09:
            this->ORA(this->immediateAddressing());
            break;
        case 0x05:
            this->ORA(this->zeroPageValueAddressing());
            break;
        case 0x15:
            this->ORA(this->zeroPageXValueAddressing());
            break;
        case 0x0D:
            this->ORA(this->absoluteValueAddressing());
            break;
        case 0x1D:
            this->ORA(this->absoluteXValueAddressing());
            break;
        case 0x19:
            this->ORA(this->absoluteYValueAddressing());
            break;
        case 0x01:
            this->ORA(this->indexedIndirectValue());
            break;
        case 0x11:
            this->ORA(this->indirectIndexedValue());
            break;
        case 0x20:
            this->JSR(this->absoluteLocationAddressing());
            break;
        case 0x60:
            this->RTS();
            break;
        case 0x40:
            this->RTI();
            break;
        case 0x00:
            this->BRK();
            break;
    }
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

void Cpu::RTI()
{
    this->statusFlags = this->pullStack();

    uint8_t lowByte = this->pullStack();
    uint8_t highByte = this->pullStack();

    this->programCounter = highByte << 8;
    this->programCounter += lowByte;

    ++this->programCounter;
}

void Cpu::BRK()
{
    uint8_t highByte = this->programCounter >> 8;
    uint8_t lowByte = this->programCounter;

    this->pushStack(highByte);
    this->pushStack(lowByte);
    this->pushStack(this->statusFlags);

    this->setBreakExecuted(true);

    uint16_t address = 0x0000;

    this->programCounter++;
    uint16_t addressLeastSignificant = 0x0000 + this->memory->getFrom(IRQ_INTERRUPT_VECTOR_LOW);

    this->programCounter++;
    uint16_t addressMostSingicant = 0x0000 + this->memory->getFrom(IRQ_INTERRUPT_VECTOR_HIGH);

    address = (addressMostSingicant << 8) + addressLeastSignificant;

    this->programCounter = address;
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
    executeInstruction(opcode);
}
