#pragma once

#include <Rom/Mapper.h>

namespace Emulator::ROM
{
    class MapperNrom : public Mapper
    {
    public:
        MapperNrom(const Cartridge& cartridge, Memory::Memory& memory);

        void map() override;

    };
}