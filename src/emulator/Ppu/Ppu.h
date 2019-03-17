#pragma once

#include <memory>
#include <initializer_list>
#include <string>

#include <Ppu/VRam.h>
#include <Memory/Memory.h>
#include <Utils/Listener.h>
#include <Utils/EventSource.h>

#define DEFAULT_PPUCNTRL  0x0000
#define DEFAULT_MASKFLAGS 0x0000
#define DEFAULT_STATUS    0x1010

#define VBLANK_FLAG       0b10000000

#define RENDER_FINISH     81840
#define VBLANK_STARTS     82181
#define SCANLINE_CYCLES   341
#define WARMUP_CYCLES     88974
#define MAX_CYCLE         89001

#define INCREMENT_BIT     0b00000100

namespace Emulator::Ppu
{
    class Ppu : public Emulator::Utils::Listener, public Emulator::Utils::EventSource
    {
    private: 
        std::shared_ptr<VRam> vram;
        std::shared_ptr<Emulator::Memory::Memory> memory;
        uint8_t oamAddress;
        struct MemoryAccessor memoryAddress;
        uint8_t controlFlags;
        uint8_t outputMaskFlags;
        uint8_t statusFlags;
        uint32_t cycleCounter;
        uint32_t warmupCycles;

        uint8_t getVramAddressIncrement();

        void setVblankStatusFLag();
        void unsetVblankStatusFlag();
        bool isVblankEnabled();

        void setOAMAddress(uint8_t address);
        void writeStatusToMemory();
        void readOAM();
        void writeOAM(uint8_t data);
        void triggerDMA(uint8_t memoryPrefix);
        void readMemory();
        void writeMemory(uint8_t data);
        void setMemoryAddress(uint8_t addressPart);
        void updateControlFlags(uint8_t newValue);
        void setOutputMaskFlags(uint8_t maskFlags);

    public:
        Ppu(std::shared_ptr<VRam> vram, std::shared_ptr<Emulator::Memory::Memory> memory);

        void notify(std::initializer_list<std::string> parameters) override;

        void operator++();
    };
}