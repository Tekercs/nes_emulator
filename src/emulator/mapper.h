#pragma once

#include <memory>

#include <cartridge.h>
#include <memory.h>
#include <cpu.h>

namespace Emulator::ROM
{
    class Mapper
    {
    private:
        const Cartridge& cartridge;
        const Memory::Memory& memory;
        const Cpu::Cpu& cpu;

    public:
        Mapper(const Cartridge& cartridge, const Memory::Memory& memory,  const Cpu::Cpu& cpu);

        virtual void map() = 0;

    };

    std::shared_ptr<Mapper> createMapper(const Cartridge& cartridge, const Memory::Memory& memory,  const Cpu::Cpu& cpu);
}
