#pragma once

#include <memory>
#include <initializer_list>
#include <string>

#include <Ppu/VRam.h>
#include <Memory/Memory.h>
#include <Utils/Listener.h>

#define DEFAULT_PPUCNTRL 0x0000
#define INCREMENT_BIT 0b00000100

namespace Emulator::Ppu
{
    class Ppu : public Emulator::Utils::Listener
    {
    private: 
        std::shared_ptr<VRam> vram;
        std::shared_ptr<Emulator::Memory::Memory> memory;
        uint8_t oamAddress;
        struct MemoryAccessor memoryAddress;
        uint8_t controlFlags;

        uint8_t getVramAddressIncrement();

        void setOAMAddress(uint8_t address);
        void readOAM();
        void writeOAM(uint8_t data);
        void triggerDMA(uint8_t memoryPrefix);
        void readMemory();
        void writeMemory(uint8_t data);
        void setMemoryAddress(uint8_t addressPart);
        void updateControlFlags(uint8_t newValue);

    public:
        Ppu(std::shared_ptr<VRam> vram, std::shared_ptr<Emulator::Memory::Memory> memory);

        void notify(std::initializer_list<std::string> parameters) override;
    };
}