#pragma once

#include <memory>

#include <Ppu/VRam.h>
#include <Memory/Memory.h>

namespace Emulator::Ppu
{
    class Ppu
    {
    private: 
        std::shared_ptr<VRam> vram;
        std::shared_ptr<Emulator::Memory::Memory> memory;
    
    public:
        Ppu(std::shared_ptr<VRam> vram, std::shared_ptr<Emulator::Memory::Memory> memory);
    };
}