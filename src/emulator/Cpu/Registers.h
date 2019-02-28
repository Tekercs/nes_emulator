#pragma once

#include <cstdint>

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

namespace Emulator::Cpu
{
    class Registers
    {
    private:
        uint16_t programCounter;
        uint8_t stackPointerOffset;
        uint8_t accumulator;
        uint8_t indexRegisterX;
        uint8_t indexRegisterY;
        uint8_t statusFlags;

    public:
        Registers();

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

        uint16_t getProgramCounter() const;
        void setProgramCounter(uint16_t programCounter);
        uint8_t getStackPointerOffset() const;
        void setStackPointerOffset(uint8_t stackPointerOffset);
        uint8_t getAccumulator() const;
        void setAccumulator(uint8_t accumulator);
        uint8_t getIndexRegisterX() const;
        void setIndexRegisterX(uint8_t indexRegisterX);
        uint8_t getIndexRegisterY() const;
        void setIndexRegisterY(uint8_t indexRegisterY);
        void setStatusFlags(uint8_t statusFlags);
        uint8_t getStatusFlags() const;

        void incrementStackPointerOffset();
        void decrementStackPointerOffset();
        void incrementProgramCounter();


    };
}
