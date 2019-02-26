#pragma once

#include <mapper.h>

namespace Emulator::ROM
{
    class MapperNrom : public Mapper
    {
    public:
        MapperNrom(const Cartridge& cartridge, const Memory::Memory& memory,  const Cpu::Cpu& cpu);

        void map() override;

    };
}