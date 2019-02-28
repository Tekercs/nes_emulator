#pragma once

#include <memory>

#include <Rom/cartridge.h>
#include <Memory/memory.h>
#include <Cpu/cpu.h>

#define MAPPER_NROM 0

namespace Emulator::ROM
{
    class Mapper
    {
    protected:
        const Cartridge& cartridge;
        Memory::Memory& memory;
        Cpu::Cpu& cpu;

    public:
        Mapper(const Cartridge& cartridge, Memory::Memory& memory, Cpu::Cpu& cpu);

        virtual void map() = 0;

    };

    std::shared_ptr<Mapper> createMapper(const Cartridge& cartridge, Memory::Memory& memory, Cpu::Cpu& cpu);
}
