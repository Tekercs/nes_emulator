#pragma once

#include <memory>
#include <initializer_list>
#include <string>

#include <Ppu/VRam.h>
#include <Memory/Memory.h>
#include <Utils/Listener.h>

#define DEFAULT_PPUCNTRL 0x0000

namespace Emulator::Ppu
{
    class Ppu : public Emulator::Utils::Listener
    {
    private: 
        std::shared_ptr<VRam> vram;
        std::shared_ptr<Emulator::Memory::Memory> memory;
        uint8_t oamAddress;
        struct MemoryAddress memoryAddress;
        uint8_t ppuControl;

    public:
        Ppu(std::shared_ptr<VRam> vram, std::shared_ptr<Emulator::Memory::Memory> memory);

        void notify(std::initializer_list<std::string> parameters) override;
    };
}