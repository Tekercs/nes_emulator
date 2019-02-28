#pragma once

#include <cstdint>
#include <memory>
#include <map>
#include <functional>

#include <Memory/memory.h>

#define STACK_POINTER              0x0100

#define FLAGBIT_CARRY              0
#define FLAGBIT_ZERO               1
#define FLAGBIT_INTERRUPT          2
#define FLAGBIT_DECMODE            3
#define FLAGBIT_BREAK              4
#define FLAGBIT_OVERFLOW           6
#define FLAGBIT_NEGATIVE           7

#define INITVAL_ACCUMULATOR        0
#define INITVAL_INDEXREGISTERX     0
#define INITVAL_INDEXREGISTERY     0
#define INITVAL_STATUSFLAGS        0x34
#define INITVAL_PROGRAMCOUNTER     0xFFFC
#define INITVAL_STACKPOINTEROFFSET 0xFD

#define IRQ_INTERRUPT_VECTOR_LOW   0xFFFE
#define IRQ_INTERRUPT_VECTOR_HIGH  0xFFFF

// TODO valoszinuleg a registereket kilehetne szedni kulon classba
namespace Emulator::Cpu
{
    class Cpu
    {
    private:
        uint16_t programCounter;
        uint8_t stackPointerOffset;
        uint8_t accumulator;
        uint8_t indexRegisterX;
        uint8_t indexRegisterY;
        uint8_t statusFlags;

        std::shared_ptr<Emulator::Memory::Memory> memory;
        std::map<uint8_t, std::function<void()>> instructions;

        void initInstructionMap();

        uint8_t pullStack();
        void pushStack(uint8_t value);

        bool checkFlagBit(uint8_t flagBit) const;
        bool isCarryRemain() const;
        bool isZeroResult() const;
        bool isInterruptsDisabled() const;
        bool isDecimalModeOn() const;
        bool isBreakExecuted() const;
        bool isOverflowHappened() const;
        bool isNegativeFlagSet() const;

        void setFlagBit(uint8_t flagBit, bool value);
        void setCarryRemain(bool value);
        void setZeroResult(bool value);
        void setInterruptsDisabled(bool value);
        void setDecimalModeOn(bool value);
        void setBreakExecuted(bool value);
        void setOverflowHappened(bool value);
        void setNegativeFlagSet(bool value);

        void PHA();
        void PLA();
        void PHP();
        void PLP();
        void SEC();
        void SED();
        void SEI();
        void CLC();
        void CLD();
        void CLI();
        void CLV();
        void TAX();
        void TAY();
        void TSX();
        void TXA();
        void TXS();
        void TYA();
        void NOP();
        void DEX();
        void INX();
        void INY();
        void DEY();
        void BIT(uint8_t value);
        void BCC(int8_t value);
        void BCS(int8_t value);
        void BMI(int8_t value);
        void BEQ(int8_t value);
        void BNE(int8_t value);
        void BPL(int8_t value);
        void BVC(int8_t value);
        void BVS(int8_t value);
        void ASLAccumulator();
        void ASL(uint16_t address);
        void AND(uint8_t value);
        void STA(uint16_t address);
        void STX(uint16_t address);
        void STY(uint16_t address);
        void ADC(uint8_t value);
        void SBC(uint8_t value);
        void JMP(uint16_t address);
        void LDA(uint8_t value);
        void LDX(uint8_t value);
        void LDY(uint8_t value);
        void DEC(uint16_t address);
        void INC(uint16_t address);
        void ROL(uint16_t address);
        void ROLAccumulator();
        void RORAccumulator();
        void ROR(uint16_t address);
        void LSRAccumulator();
        void LSR(uint16_t address);
        void CMP(uint8_t value);
        void CPX(uint8_t value);
        void CPY(uint8_t value);
        void EOR(uint8_t value);
        void ORA(uint8_t value);
        void JSR(uint16_t address);
        void RTS();
        void RTI();
        void BRK();

        uint8_t immediateAddressing();
        uint8_t zeroPageAddressing();
        uint8_t zeroPageXAddressing();
        uint8_t zeroPageYAddressing();
        uint8_t zeroPageValueAddressing();
        uint8_t zeroPageXValueAddressing();
        uint8_t zeroPageYValueAddressing();
        uint8_t absoluteValueAddressing();
        uint8_t absoluteXValueAddressing();
        uint8_t absoluteYValueAddressing();
        uint16_t absoluteLocationAddressing();
        uint16_t absoluteXLocationAddressing();
        uint16_t absoluteYLocationAddressing();
        uint16_t indirectAddress();
        uint16_t indexedIndirectAddress();
        uint16_t indirectIndexedAddress();
        uint8_t indexedIndirectValue();
        uint8_t indirectIndexedValue();

    public:
        explicit Cpu(std::shared_ptr<Emulator::Memory::Memory> memory);

        void operator++();
    };
}