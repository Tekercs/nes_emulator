#include "Cpu.h"

#include <utility>
#include <memory>

#include <Memory/Memory.h>
#include <Cpu/Registers.h>

using namespace std;
using namespace Emulator::Cpu;
using namespace Emulator::Memory;

Cpu::Cpu()
: memory(make_shared<Memory::Memory>())
, registers(make_shared<Registers>())
, nmi(false)
{}

Cpu::Cpu(std::shared_ptr<Emulator::Memory::Memory> memory, std::shared_ptr<Emulator::Cpu::Registers> registers)
: memory(move(memory))
, registers(move(registers))
, nmi(false)
{ }

uint8_t Cpu::pullStack()
{
    this->registers->incrementStackPointerOffset();
    uint16_t stackPointer = STACK_POINTER + this->registers->getStackPointerOffset();

    return this->memory->getFrom(stackPointer);
}

void Cpu::pushStack(uint8_t value)
{
    uint16_t stackPointer = STACK_POINTER + this->registers->getStackPointerOffset();
    this->registers->decrementStackPointerOffset();

    this->memory->setAt(stackPointer, value);
}

void Cpu::executeInstruction(uint8_t opcode)
{
    switch (opcode)
    {
        case 0x69:
            this->ADC(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x65:
            this->ADC(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x75:
            this->ADC(this->zeroPageXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x6D:
            this->ADC(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x7D:
            this->ADC(this->absoluteXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x79:
            this->ADC(this->absoluteYValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x61:
            this->ADC(this->indexedIndirectValue());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x71:
            this->ADC(this->indirectIndexedValue());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0x29:
            this->AND(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x25:
            this->AND(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0x35:
            this->AND(this->zeroPageXValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0x2D:
            this->AND(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x3D:
            this->AND(this->absoluteXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x39:
            this->AND(this->absoluteYValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x21:
            this->AND(this->indexedIndirectValue());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x31:
            this->AND(this->indirectIndexedValue());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0x0A:
            this->ASLAccumulator();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x06:
            this->ASL(this->zeroPageAddressing());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0x16:
            this->ASL(this->zeroPageXAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x0E:
            this->ASL(this->absoluteLocationAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x1E:
            this->ASL(this->absoluteXLocationAddressing());
            this->notifyListeners({"cyclepassed", "7"});
            break;
        case 0x90:
            this->BCC(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xB0:
            this->BCS(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xF0:
            this->BEQ(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x24:
            this->BIT(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x2C:
            this->BIT(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0x30:
            this->BMI(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xD0:
            this->BNE(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x10:
            this->BPL(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x50:
            this->BVC(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x70:
            this->BVS(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xC6:
            this->DEC(this->zeroPageAddressing());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0xD6:
            this->DEC(this->zeroPageXAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0xCE:
            this->DEC(this->absoluteLocationAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0xDE:
            this->DEC(this->absoluteXLocationAddressing());
            this->notifyListeners({"cyclepassed", "7"});
            break;
        case 0xCA:
            this->DEX();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x88:
            this->DEY();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xE6:
            this->INC(this->zeroPageAddressing());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0xF6:
            this->INC(this->zeroPageXAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0xEE:
            this->INC(this->absoluteLocationAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0xFE:
            this->INC(this->absoluteXLocationAddressing());
            this->notifyListeners({"cyclepassed", "7"});
            break;
        case 0xE8:
            this->INX();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xC8:
            this->INY();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xA9:
            this->LDA(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xA5:
            this->LDA(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0xB5:
            this->LDA(this->zeroPageXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xAD:
            this->LDA(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xBD:
            this->LDA(this->absoluteXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xB9:
            this->LDA(this->absoluteYValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xA1:
            this->LDA(this->indexedIndirectValue());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0xB1:
            this->LDA(this->indirectIndexedValue());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0xA2:
            this->LDX(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xA6:
            this->LDX(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0xB6:
            this->LDX(this->zeroPageYValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xAE:
            this->LDX(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xBE:
            this->LDX(this->absoluteYValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xA0:
            this->LDY(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xA4:
            this->LDY(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0xB4:
            this->LDY(this->zeroPageXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xAC:
            this->LDY(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xBC:
            this->LDY(this->absoluteXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x48:
            this->PHA();
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0x68:
            this->PLA();
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x08:
            this->PHP();
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0x28:
            this->PLP();
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x38:
            this->SEC();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xF8:
            this->SED();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x78:
            this->SEI();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x18:
            this->CLC();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xD8:
            this->CLD();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x58:
            this->CLI();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xB8:
            this->CLV();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xAA:
            this->TAX();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xA8:
            this->TAY();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xBA:
            this->TSX();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x8A:
            this->TXA();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x9A:
            this->TXS();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x98:
            this->TYA();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x4C:
            this->JMP(this->absoluteLocationAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0x6C:
            this->JMP(this->indirectAddress());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0xE9:
            this->SBC(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xE5:
            this->SBC(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0xF5:
            this->SBC(this->zeroPageXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xED:
            this->SBC(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xFD:
            this->SBC(this->absoluteXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xF9:
            this->SBC(this->absoluteYValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xE1:
            this->SBC(this->indexedIndirectValue());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0xF1:
            this->SBC(this->indirectIndexedValue());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0x85:
            this->STA(this->zeroPageAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0x95:
            this->STA(this->zeroPageXAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x8D:
            this->STA(this->absoluteLocationAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x9D:
            this->STA(this->absoluteXLocationAddressing());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0x99:
            this->STA(this->absoluteYLocationAddressing());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0x81:
            this->STA(this->indexedIndirectAddress());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x91:
            this->STA(this->indirectIndexedAddress());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x86:
            this->STX(this->zeroPageAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0x96:
            this->STX(this->zeroPageYAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x8E:
            this->STX(this->absoluteLocationAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x84:
            this->STY(this->zeroPageAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0x94:
            this->STY(this->zeroPageXAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x8C:
            this->STY(this->absoluteLocationAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xEA:
            this->NOP();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x2A:
            this->ROLAccumulator();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x26:
            this->ROL(this->zeroPageAddressing());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0x36:
            this->ROL(this->zeroPageXAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x2E:
            this->ROL(this->absoluteLocationAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x3E:
            this->ROL(this->absoluteXLocationAddressing());
            this->notifyListeners({"cyclepassed", "7"});
            break;
        case 0x6A:
            this->RORAccumulator();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x66:
            this->ROR(this->zeroPageAddressing());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0x76:
            this->ROR(this->zeroPageXAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x6E:
            this->ROR(this->absoluteLocationAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x7E:
            this->ROR(this->absoluteXLocationAddressing());
            this->notifyListeners({"cyclepassed", "7"});
            break;
        case 0x4A:
            this->LSRAccumulator();
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x46:
            this->LSR(this->zeroPageAddressing());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0x56:
            this->LSR(this->zeroPageXAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x4E:
            this->LSR(this->absoluteLocationAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x5E:
            this->LSR(this->absoluteXLocationAddressing());
            this->notifyListeners({"cyclepassed", "7"});
            break;
        case 0xC9:
            this->CMP(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xC5:
            this->CMP(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0xD5:
            this->CMP(this->zeroPageXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xCD:
            this->CMP(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xDD:
            this->CMP(this->absoluteXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xD9:
            this->CMP(this->absoluteYValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xC1:
            this->CMP(this->indexedIndirectValue());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0xD1:
            this->CMP(this->indirectIndexedValue());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0xE0:
            this->CPX(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xE4:
            this->CPX(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0xEC:
            this->CPX(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0xC0:
            this->CPY(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0xC4:
            this->CPY(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0xCC:
            this->CPY(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x49:
            this->EOR(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x45:
            this->EOR(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0x55:
            this->EOR(this->zeroPageXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x4D:
            this->EOR(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x5D:
            this->EOR(this->absoluteXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x59:
            this->EOR(this->absoluteYValueAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x41:
            this->EOR(this->indexedIndirectValue());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x51:
            this->EOR(this->indirectIndexedValue());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0x09:
            this->ORA(this->immediateAddressing());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x05:
            this->ORA(this->zeroPageValueAddressing());
            this->notifyListeners({"cyclepassed", "3"});
            break;
        case 0x15:
            this->ORA(this->zeroPageXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x0D:
            this->ORA(this->absoluteValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x1D:
            this->ORA(this->absoluteXValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x19:
            this->ORA(this->absoluteYValueAddressing());
            this->notifyListeners({"cyclepassed", "4"});
            break;
        case 0x01:
            this->ORA(this->indexedIndirectValue());
            this->notifyListeners({"cyclepassed", "2"});
            break;
        case 0x11:
            this->ORA(this->indirectIndexedValue());
            this->notifyListeners({"cyclepassed", "5"});
            break;
        case 0x20:
            this->JSR(this->absoluteLocationAddressing());
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x60:
            this->RTS();
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x40:
            this->RTI();
            this->notifyListeners({"cyclepassed", "6"});
            break;
        case 0x00:
            this->BRK();
            this->notifyListeners({"cyclepassed", "7"});
            break;
    }
}



void Cpu::PHA()
{
    this->pushStack(this->registers->getAccumulator());
    this->registers->incrementProgramCounter();
}

void Cpu::PLA()
{
    this->registers->setAccumulator(this->pullStack());

    this->registers->setZeroResult(this->registers->getAccumulator() == 0);
    this->registers->setNegativeFlagSet((this->registers->getAccumulator() & 0B10000000) != 0);
    this->registers->incrementProgramCounter();
}

void Cpu::PHP()
{
    this->pushStack(this->registers->getStatusFlags() | 0x10);
    this->registers->incrementProgramCounter();
}

void Cpu::PLP()
{
    uint8_t pulledFlags = this->pullStack();
    uint8_t currentFlags = this->registers->getStatusFlags();

    uint8_t result = (pulledFlags & 0B11001111) + (currentFlags & 0B00110000);

    this->registers->setStatusFlags(result);
    this->registers->incrementProgramCounter();
}

void Cpu::SEC()
{
    this->registers->setCarryRemain(true);
    this->registers->incrementProgramCounter();
}

void Cpu::SED()
{
    this->registers->setDecimalModeOn(true);
    this->registers->incrementProgramCounter();
}

void Cpu::SEI()
{
    this->registers->setInterruptsDisabled(true);
    this->registers->incrementProgramCounter();
}

void Cpu::CLC()
{
    this->registers->setCarryRemain(false);
    this->registers->incrementProgramCounter();
}

void Cpu::CLD()
{
    this->registers->setDecimalModeOn(false);
    this->registers->incrementProgramCounter();
}

void Cpu::CLI()
{
    this->registers->setInterruptsDisabled(false);
    this->registers->incrementProgramCounter();
}

void Cpu::CLV()
{
    this->registers->setOverflowHappened(false);
    this->registers->incrementProgramCounter();
}

void Cpu::LDA(uint8_t value)
{
    this->registers->setAccumulator(value);

    this->registers->setZeroResult(this->registers->getAccumulator() == 0);
    this->registers->setNegativeFlagSet((this->registers->getAccumulator() & 0B10000000) != 0);

    this->registers->incrementProgramCounter();
}

void Cpu::LDX(uint8_t value)
{
    this->registers->setIndexRegisterX(value);

    this->registers->setZeroResult(this->registers->getIndexRegisterX() == 0);
    this->registers->setNegativeFlagSet((this->registers->getIndexRegisterX() & 0B10000000) != 0);

    this->registers->incrementProgramCounter();
}

void Cpu::LDY(uint8_t value)
{
    this->registers->setIndexRegisterY(value);

    this->registers->setZeroResult(this->registers->getIndexRegisterY() == 0);
    this->registers->setNegativeFlagSet((this->registers->getIndexRegisterY() & 0B10000000) != 0);

    this->registers->incrementProgramCounter();
}

void Cpu::JMP(uint16_t address)
{
    this->registers->setProgramCounter(address);
}

void Cpu::ADC(uint8_t value)
{
    uint32_t result = this->registers->getAccumulator() + value + this->registers->isCarryRemain();

    this->registers->setCarryRemain(result > 0xFF);

    this->registers->setZeroResult((result & 0xFF) == 0);
    this->registers->setOverflowHappened(~(this->registers->getAccumulator() ^ value) & (this->registers->getAccumulator() ^ result) & 0B10000000);
    this->registers->setNegativeFlagSet(result & 0B10000000);

    this->registers->setAccumulator(static_cast<uint8_t>(result));

    this->registers->incrementProgramCounter();
}

void Cpu::SBC(uint8_t value)
{
    this->ADC(~(value));
}

void Cpu::STA(uint16_t address)
{
    this->memory->setAt(address, this->registers->getAccumulator());
    this->registers->incrementProgramCounter();
}

void Cpu::STX(uint16_t address)
{
    this->memory->setAt(address, this->registers->getIndexRegisterX());
    this->registers->incrementProgramCounter();
}

void Cpu::STY(uint16_t address)
{
    this->memory->setAt(address, this->registers->getIndexRegisterY());
    this->registers->incrementProgramCounter();
}

void Cpu::TAX()
{
    this->registers->setIndexRegisterX(this->registers->getAccumulator());

    this->registers->setZeroResult(this->registers->getIndexRegisterX() == 0);
    this->registers->setNegativeFlagSet((this->registers->getIndexRegisterX() & 0B10000000) > 0);

    this->registers->incrementProgramCounter();
}

void Cpu::TAY()
{
    this->registers->setIndexRegisterY(this->registers->getAccumulator());

    this->registers->setZeroResult(this->registers->getIndexRegisterY() == 0);
    this->registers->setNegativeFlagSet((this->registers->getIndexRegisterY() & 0B10000000) > 0);

    this->registers->incrementProgramCounter();
}

void Cpu::TSX()
{
    this->registers->setIndexRegisterX(this->registers->getStackPointerOffset());

    this->registers->setZeroResult(this->registers->getIndexRegisterX() == 0);
    this->registers->setNegativeFlagSet((this->registers->getIndexRegisterX() & 0B10000000) > 0);

    this->registers->incrementProgramCounter();
}

void Cpu::TXA()
{
    this->registers->setAccumulator(this->registers->getIndexRegisterX());

    this->registers->setZeroResult(this->registers->getAccumulator() == 0);
    this->registers->setNegativeFlagSet((this->registers->getAccumulator() & 0B10000000) > 0);

    this->registers->incrementProgramCounter();
}

void Cpu::TXS()
{
    this->registers->setStackPointerOffset(this->registers->getIndexRegisterX());

    this->registers->incrementProgramCounter();
}

void Cpu::TYA()
{
    this->registers->setAccumulator(this->registers->getIndexRegisterY());

    this->registers->setZeroResult(this->registers->getAccumulator() == 0);
    this->registers->setNegativeFlagSet((this->registers->getAccumulator() & 0B10000000) > 0);

    this->registers->incrementProgramCounter();
}

void Cpu::AND(uint8_t value)
{
    this->registers->setAccumulator(this->registers->getAccumulator() & value);

    this->registers->setZeroResult(this->registers->getAccumulator() == 0);
    this->registers->setNegativeFlagSet((this->registers->getAccumulator() & 0B10000000) > 0);

    this->registers->incrementProgramCounter();
}

void Cpu::NOP()
{
    this->registers->incrementProgramCounter();
}

void Cpu::ASL(uint16_t address)
{
    uint8_t value = this->memory->getFrom(address);
    uint16_t shiftResult = value << 1;
    value = shiftResult;

    this->registers->setCarryRemain(shiftResult > 0xFF);
    this->registers->setZeroResult(value == 0);
    this->registers->setNegativeFlagSet((value & 0B10000000) > 0);

    this->memory->setAt(address, value);
    this->registers->incrementProgramCounter();
}

void Cpu::ASLAccumulator()
{
    uint16_t shiftResult = this->registers->getAccumulator() << 1;
    this->registers->setAccumulator(shiftResult);

    this->registers->setCarryRemain(shiftResult > 0xFF);
    this->registers->setZeroResult(this->registers->getAccumulator() == 0);
    this->registers->setNegativeFlagSet((this->registers->getAccumulator() & 0B10000000) > 0);

    this->registers->incrementProgramCounter();
}

void Cpu::BCC(int8_t value)
{
    if (!this->registers->isCarryRemain())
        this->registers->setProgramCounter(this->registers->getProgramCounter() + value);

    this->registers->incrementProgramCounter();
}

void Cpu::BCS(int8_t value)
{
    if (this->registers->isCarryRemain())
        this->registers->setProgramCounter(this->registers->getProgramCounter() + value);

    this->registers->incrementProgramCounter();
}

void Cpu::BEQ(int8_t value)
{
    if (this->registers->isZeroResult())
        this->registers->setProgramCounter(this->registers->getProgramCounter() + value);

    this->registers->incrementProgramCounter();
}

void Cpu::BMI(int8_t value)
{
    if (this->registers->isNegativeFlagSet())
        this->registers->setProgramCounter(this->registers->getProgramCounter() + value);

    this->registers->incrementProgramCounter();
}

void Cpu::BNE(int8_t value)
{
    if (!this->registers->isZeroResult())
        this->registers->setProgramCounter(this->registers->getProgramCounter() + value);

    this->registers->incrementProgramCounter();
}

void Cpu::BPL(int8_t value)
{
    if (!this->registers->isNegativeFlagSet())
        this->registers->setProgramCounter(this->registers->getProgramCounter() + value);

    this->registers->incrementProgramCounter();
}

void Cpu::BVC(int8_t value)
{
    if (!this->registers->isOverflowHappened())
        this->registers->setProgramCounter(this->registers->getProgramCounter() + value);

    this->registers->incrementProgramCounter();
}

void Cpu::BVS(int8_t value)
{
    if (this->registers->isOverflowHappened())
        this->registers->setProgramCounter(this->registers->getProgramCounter() + value);

    this->registers->incrementProgramCounter();
}

void Cpu::BIT(uint8_t value)
{
    uint8_t result = this->registers->getAccumulator() & value;

    this->registers->setNegativeFlagSet((value & 0B10000000));
    this->registers->setOverflowHappened((value & 0B01000000));
    this->registers->setZeroResult(result == 0);

    this->registers->incrementProgramCounter();
}

void Cpu::DEC(uint16_t address)
{
    uint8_t value = this->memory->getFrom(address);
    --value;

    this->registers->setZeroResult(value == 0);
    this->registers->setNegativeFlagSet(value & 0B10000000);

    this->memory->setAt(address, value);

    this->registers->incrementProgramCounter();
}

void Cpu::INC(uint16_t address)
{
    uint8_t value = this->memory->getFrom(address);
    ++value;

    this->registers->setZeroResult(value == 0);
    this->registers->setNegativeFlagSet(value & 0B10000000);

    this->memory->setAt(address, value);

    this->registers->incrementProgramCounter();
}

void Cpu::DEX()
{
    this->registers->setIndexRegisterX(this->registers->getIndexRegisterX() -1);

    this->registers->setZeroResult(this->registers->getIndexRegisterX() == 0);
    this->registers->setNegativeFlagSet(this->registers->getIndexRegisterX() & 0B10000000);

    this->registers->incrementProgramCounter();
}

void Cpu::INX()
{
    this->registers->setIndexRegisterX(this->registers->getIndexRegisterX() +1);

    this->registers->setZeroResult(this->registers->getIndexRegisterX() == 0);
    this->registers->setNegativeFlagSet(this->registers->getIndexRegisterX() & 0B10000000);

    this->registers->incrementProgramCounter();
}

void Cpu::DEY()
{
    this->registers->setIndexRegisterY(this->registers->getIndexRegisterY() -1);

    this->registers->setZeroResult(this->registers->getIndexRegisterY() == 0);
    this->registers->setNegativeFlagSet(this->registers->getIndexRegisterY() & 0B10000000);

    this->registers->incrementProgramCounter();
}

void Cpu::INY()
{
    this->registers->setIndexRegisterY(this->registers->getIndexRegisterY() +1);

    this->registers->setZeroResult(this->registers->getIndexRegisterY() == 0);
    this->registers->setNegativeFlagSet(this->registers->getIndexRegisterY() & 0B10000000);

    this->registers->incrementProgramCounter();
}

void Cpu::ROLAccumulator()
{
    uint16_t newValue = this->registers->getAccumulator();
    newValue = newValue << 1;

    if (this->registers->isCarryRemain())
        ++newValue;

    this->registers->setCarryRemain(newValue & 0B100000000);
    this->registers->setAccumulator(newValue);

    this->registers->setNegativeFlagSet(this->registers->getAccumulator() & 0B10000000);
    this->registers->setZeroResult(this->registers->getAccumulator() == 0);

    this->registers->incrementProgramCounter();
}

void Cpu::ROL(uint16_t address)
{
    uint16_t newValue = this->memory->getFrom(address);
    newValue = newValue << 1;

    if (this->registers->isCarryRemain())
        ++newValue;

    this->registers->setCarryRemain(newValue & 0B100000000);
    this->memory->setAt(address, newValue);

    this->registers->setNegativeFlagSet(newValue & 0B10000000);
    this->registers->setZeroResult(newValue == 0);

    this->registers->incrementProgramCounter();
}

void Cpu::RORAccumulator()
{
    uint16_t newValue = (this->registers->isCarryRemain()) ? 1 << 8 : 0;
    newValue += this->registers->getAccumulator();

    this->registers->setCarryRemain(newValue & 0b1);

    newValue = newValue >> 1;
    this->registers->setAccumulator(newValue);

    this->registers->setZeroResult(this->registers->getAccumulator() == 0);
    this->registers->setNegativeFlagSet(newValue & 0B10000000);

    this->registers->incrementProgramCounter();
}

void Cpu::ROR(uint16_t address)
{
    uint16_t newValue = (this->registers->isCarryRemain()) ? 1 << 8 : 0;
    newValue += this->memory->getFrom(address);

    this->registers->setCarryRemain(newValue & 0b1);

    newValue = newValue >> 1;
    this->memory->setAt(address, newValue);

    this->registers->setNegativeFlagSet(newValue & 0B10000000);
    this->registers->setZeroResult(newValue == 0);

    this->registers->incrementProgramCounter();
}

void Cpu::LSRAccumulator()
{
    uint8_t newValue = this->registers->getAccumulator();

    this->registers->setCarryRemain(newValue & 0b1);

    newValue = newValue >> 1;
    this->registers->setAccumulator(newValue);

    this->registers->setZeroResult(this->registers->getAccumulator() == 0);
    this->registers->setNegativeFlagSet(newValue & 0B10000000);

    this->registers->incrementProgramCounter();
}

void Cpu::LSR(uint16_t address)
{
    uint8_t newValue = this->memory->getFrom(address);

    this->registers->setCarryRemain(newValue & 0b1);

    newValue = newValue >> 1;
    this->memory->setAt(address, newValue);

    this->registers->setNegativeFlagSet(newValue & 0B10000000);
    this->registers->setZeroResult(newValue == 0);

    this->registers->incrementProgramCounter();
}

void Cpu::CMP(uint8_t value)
{
    this->registers->setCarryRemain(this->registers->getAccumulator() >= value);
    this->registers->setZeroResult(this->registers->getAccumulator() == value);

    this->registers->setNegativeFlagSet((this->registers->getAccumulator() - value) & 0B10000000);

    this->registers->incrementProgramCounter();
}

void Cpu::CPX(uint8_t value)
{
    this->registers->setCarryRemain(this->registers->getIndexRegisterX() >= value);
    this->registers->setZeroResult(this->registers->getIndexRegisterX() == value);

    this->registers->setNegativeFlagSet((this->registers->getIndexRegisterX() - value) & 0B10000000);

    this->registers->incrementProgramCounter();
}

void Cpu::CPY(uint8_t value)
{
    this->registers->setCarryRemain(this->registers->getIndexRegisterY() >= value);
    this->registers->setZeroResult(this->registers->getIndexRegisterY() == value);

    this->registers->setNegativeFlagSet((this->registers->getIndexRegisterY() - value) & 0B10000000);

    this->registers->incrementProgramCounter();
}

void Cpu::EOR(uint8_t value)
{
    this->registers->setAccumulator(this->registers->getAccumulator() ^ value);

    this->registers->setZeroResult(this->registers->getAccumulator() == 0);
    this->registers->setNegativeFlagSet((this->registers->getAccumulator() & 0B10000000) > 0);

    this->registers->incrementProgramCounter();
}

void Cpu::ORA(uint8_t value)
{
    this->registers->setAccumulator(this->registers->getAccumulator() | value);

    this->registers->setZeroResult(this->registers->getAccumulator() == 0);
    this->registers->setNegativeFlagSet((this->registers->getAccumulator() & 0B10000000) > 0);

    this->registers->incrementProgramCounter();
}

void Cpu::JSR(uint16_t address)
{
    uint8_t highByte = this->registers->getProgramCounter() >> 8;
    uint8_t lowByte = this->registers->getProgramCounter();

    this->pushStack(highByte);
    this->pushStack(lowByte);

    this->registers->setProgramCounter(address);
}

void Cpu::RTS()
{
    uint8_t lowByte = this->pullStack();
    uint8_t highByte = this->pullStack();

    this->registers->setProgramCounter((highByte << 8) + lowByte );


    this->registers->incrementProgramCounter();
}

void Cpu::RTI()
{
    uint8_t pulledFlags = this->pullStack();
    uint8_t currentFlags = this->registers->getStatusFlags();

    uint8_t result = (pulledFlags & 0B11001111) + (currentFlags & 0B00110000);
    this->registers->setStatusFlags(result);

    uint8_t lowByte = this->pullStack();
    uint8_t highByte = this->pullStack();

    this->registers->setProgramCounter((highByte << 8) + lowByte );
}

void Cpu::BRK()
{
    if (this->registers->isInterruptsDisabled())
        return;

    uint8_t highByte = this->registers->getProgramCounter() >> 8;
    uint8_t lowByte = this->registers->getProgramCounter();

    this->pushStack(highByte);
    this->pushStack(lowByte);
    this->pushStack(this->registers->getStatusFlags());

    this->registers->setBreakExecuted(true);

    uint16_t address = 0x0000;

    this->registers->incrementProgramCounter();
    uint16_t addressLeastSignificant = 0x0000 + this->memory->getFrom(IRQ_INTERRUPT_VECTOR_LOW);

    this->registers->incrementProgramCounter();
    uint16_t addressMostSingicant = 0x0000 + this->memory->getFrom(IRQ_INTERRUPT_VECTOR_HIGH);

    address = (addressMostSingicant << 8) + addressLeastSignificant;

    this->registers->setProgramCounter(address);
}

uint8_t Cpu::immediateAddressing()
{
    this->registers->incrementProgramCounter();
    return this->memory->getFrom(this->registers->getProgramCounter());
}

uint8_t Cpu::zeroPageAddressing()
{
    this->registers->incrementProgramCounter();
    return this->memory->getFrom(this->registers->getProgramCounter());
}

uint8_t Cpu::zeroPageXAddressing()
{
    this->registers->incrementProgramCounter();
    uint8_t zeroPageAddress = this->memory->getFrom(this->registers->getProgramCounter());

    return zeroPageAddress + this->registers->getIndexRegisterX();
}

uint8_t Cpu::zeroPageYAddressing()
{
    this->registers->incrementProgramCounter();
    uint8_t zeroPageAddress = this->memory->getFrom(this->registers->getProgramCounter());

    return zeroPageAddress + this->registers->getIndexRegisterY();
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

    this->registers->incrementProgramCounter();
    uint16_t addressLeastSignificant = 0x0000 + this->memory->getFrom(this->registers->getProgramCounter());

    this->registers->incrementProgramCounter();
    uint16_t addressMostSingicant = 0x0000 + this->memory->getFrom(this->registers->getProgramCounter());

    address = (addressMostSingicant << 8) + addressLeastSignificant;

    return address;
}

uint16_t Cpu::absoluteXLocationAddressing()
{
    return this->absoluteLocationAddressing() + this->registers->getIndexRegisterX();
}

uint16_t Cpu::absoluteYLocationAddressing()
{
    return this->absoluteLocationAddressing() + this->registers->getIndexRegisterY();
}

uint16_t Cpu::indirectAddress()
{
    uint16_t address = 0x0000;

    this->registers->incrementProgramCounter();
    uint16_t addressLeastSignificant = 0x0000 + this->memory->getFrom(this->registers->getProgramCounter());

    this->registers->incrementProgramCounter();
    uint16_t addressMostSingicant = 0x0000 + this->memory->getFrom(this->registers->getProgramCounter());

    address = (addressMostSingicant << 8) + addressLeastSignificant;

    addressLeastSignificant = 0x0000 + this->memory->getFrom(address);

    // this is for implementing the actual bug in the 6502 indirect JMP
    if ((address & 0x00FF) == 0x00FF)
        address = address & 0xFF00;
    else
        ++address;

    addressMostSingicant = 0x0000 + this->memory->getFrom(address);

    address = (addressMostSingicant << 8) + addressLeastSignificant;

    return address;

}

uint16_t Cpu::indexedIndirectAddress()
{
    this->registers->incrementProgramCounter();
    uint8_t zeroPageAddress = this->memory->getFrom(this->registers->getProgramCounter());

    zeroPageAddress += this->registers->getIndexRegisterX();

    uint16_t address = 0x0000;
    uint16_t addressLeastSignificant = 0x0000 + this->memory->getFrom(zeroPageAddress);

    ++zeroPageAddress;
    uint16_t addressMostSingicant = 0x0000 + this->memory->getFrom(zeroPageAddress);

    address = (addressMostSingicant << 8) + addressLeastSignificant;

    return address;
}

uint16_t Cpu::indirectIndexedAddress()
{
    this->registers->incrementProgramCounter();
    uint8_t zeroPageAddress = this->memory->getFrom(this->registers->getProgramCounter());

    uint16_t address = 0x0000;
    uint16_t addressLeastSignificant = 0x0000 + this->memory->getFrom(zeroPageAddress);

    ++zeroPageAddress;
    uint16_t addressMostSingicant = 0x0000 + this->memory->getFrom(zeroPageAddress);

    address = (addressMostSingicant << 8) + addressLeastSignificant;
    address += this->registers->getIndexRegisterY();

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
    if (this->nmi)
        this->NMI();

    uint8_t opcode = this->memory->getFrom(this->registers->getProgramCounter());
    executeInstruction(opcode);
}

void Cpu::notify(std::initializer_list<std::string> parameters)
{
    auto eventName = *parameters.begin();

    if (eventName == "nmiinterrupt")
        this->nmi = true;
}

void Cpu::NMI()
{
    uint8_t highByte = this->registers->getProgramCounter() >> 8;
    uint8_t lowByte = this->registers->getProgramCounter();

    this->pushStack(highByte);
    this->pushStack(lowByte);
    this->pushStack(this->registers->getStatusFlags());

    uint16_t address = (this->memory->getFrom(NMI_UPPER) << 8) + this->memory->getFrom(NMI_LOWER);

    this->registers->setProgramCounter(address);

    this->nmi = false;
}

void Cpu::reset()
{
    uint16_t programCounter = (this->memory->getFrom(RESET_UPPER) << 8) + this->memory->getFrom(RESET_LOWER);

    this->registers->setProgramCounter(programCounter);
    this->registers->setStackPointerOffset(this->registers->getStackPointerOffset() - 3);
}
