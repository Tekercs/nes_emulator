#pragma once

#include <cstdint>
#include <memory>
#include <map>
#include <functional>

#include <memory.h>

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

    public:
        explicit Cpu(std::shared_ptr<Emulator::Memory::Memory> memory);

    };
}