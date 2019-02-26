#pragma once

#include <mapper.h>

namespace Emulator::ROM
{
    class MapperNrom : public Mapper
    {
    public:
        MapperNrom(const Cartridge& cartridge, Memory::Memory& memory, Cpu::Cpu& cpu);

        void map() override;

    };
}