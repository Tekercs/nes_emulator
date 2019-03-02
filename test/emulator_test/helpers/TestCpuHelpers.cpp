#include "TestCpuHelpers.h"

#include <sstream>
#include <iomanip>

using namespace std;
using namespace Emulator::Memory;
using namespace Emulator::Cpu;

std::string parseCurrentStateLog(const Emulator::Memory::Memory& memory, const Emulator::Cpu::Registers& registers)
{
    stringstream sstream;
    sstream << hex << registers.getProgramCounter() << " ";
    
    switch (registers.getProgramCounter())
    {
        case 0x69: sstream << "0x69 " << hex << memory.getFrom(registers.getProgramCounter() +1); break; 
        /*
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

        */
    }

    sstream << "A:" << hex << registers.getAccumulator();
    sstream << "Y:" << hex << registers.getIndexRegisterX();
    sstream << "X:" << hex << registers.getIndexRegisterY();
    sstream << "P:" << hex << registers.getStatusFlags();
    sstream << "SP:" << hex << registers.getStackPointerOffset();

    return sstream.str();
}
