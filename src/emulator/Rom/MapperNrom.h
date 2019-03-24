#pragma once

#include <Rom/Mapper.h>
#include <Ppu/VRam.h>

namespace Emulator::ROM
{
    class MapperNrom : public Mapper
    {
    public:
        MapperNrom(const Cartridge& cartridge, Memory::Memory& memory, Ppu::VRam& vram);

        void map() override;

    };
}