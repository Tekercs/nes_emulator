#pragma once

#include <memory>

#include <Rom/Cartridge.h>
#include <Memory/Memory.h>
#include <Cpu/Cpu.h>
#include <Ppu/VRam.h>

#define MAPPER_NROM 0

namespace Emulator::ROM
{
    class Mapper
    {
    protected:
        const Cartridge& cartridge;
        Memory::Memory& memory;
        Ppu::VRam& vram;

    public:
        Mapper(const Cartridge& cartridge, Memory::Memory& memory, Ppu::VRam& vram);

        virtual void map() = 0;

    };

    std::shared_ptr<Mapper> createMapper(const Cartridge &cartridge, Memory::Memory &memory, Ppu::VRam &vram);
}
