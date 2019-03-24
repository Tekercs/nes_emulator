#include <catch.hpp>

#include <string>
#include <memory>
#include <vector>

#include <Ppu/VRam.h>
#include <Ppu/Ppu.h>
#include <Memory/Memory.h>
#include <Ppu/Renderer.h>

#include "helpers/DummyRenderer.h"

using namespace std;
using namespace Emulator::Ppu;
using namespace Emulator::Memory;

SCENARIO("accessing vram via memory mappings")
{
    GIVEN("empty memory, vram and inited PPU")
    {
        shared_ptr<Memory> memory = make_shared<Memory>();
        shared_ptr<VRam> vram = make_shared<VRam>(HORIZONTAL);
        shared_ptr<DummyRenderer> renderer = make_shared<DummyRenderer>();

        Ppu ppu(vram, memory, renderer);
        memory->subscribe(&ppu);

        WHEN("writing OAMADDR and OAMDATA")
        {
            memory->setAt(0x2003, 0x01);
            memory->setAt(0x2004, 0x02);

            THEN("the vram value on the given adderss changed")
            {
                REQUIRE(vram->readOAM(0x01) == 0x02);
            }
        }

        WHEN("writing the OAMADDR once and OAMDATA twice")
        {
            memory->setAt(0x2003, 0x02);
            memory->setAt(0x2004, 0x02);

            THEN ("the VRAM value is set")
            {
                REQUIRE((vram->readOAM(0x02) == 0x02));   
            }

            THEN("write once more to the OAMADDR and check if the preivous one is unaffeceted and the new one is set")
            {
                memory->setAt(0x2004, 0x06);
                REQUIRE((vram->readOAM(0x02)) == 0x02);
                REQUIRE((vram->readOAM(0x03)) == 0x06);
            }
        }
    }

    GIVEN("empty memory, a preset vram and a gpu")
    {
        shared_ptr<DummyRenderer> renderer = make_shared<DummyRenderer>();
        shared_ptr<Memory> memory = make_shared<Memory>();
        shared_ptr<VRam> vram = make_shared<VRam>(HORIZONTAL);
        vram->writeOAM(0x05, 0xAA);

        Ppu ppu(vram, memory, renderer);
        memory->subscribe(&ppu);

        WHEN("writing to OAMADDR the given address")
        {
            memory->setAt(0x2003, 0x05);

            THEN ("reading OAMDATA should return the data at the given OAM address from the vram")
            {
                REQUIRE((memory->getFrom(0x2004)) == 0xAA);
            }
        } 

    }

    GIVEN ("an empty vram, and a preset memory, and a ppu")
    {
        shared_ptr<DummyRenderer> renderer = make_shared<DummyRenderer>();
        shared_ptr<Memory> memory = make_shared<Memory>();
        for(auto i = 0; i < 0x100; ++i)
            memory->setAt((0x0000 + i), 0xAA);
        for(auto i = 0; i < 0xcc; ++i)
            memory->setAt((0x0000 + i), 0xBB);

        shared_ptr<VRam> vram = make_shared<VRam>(HORIZONTAL);
        Ppu ppu(vram, memory, renderer);
        memory->subscribe(&ppu);

        WHEN("write to OAMDMA register and trigegr DMA")
        {
            memory->setAt(0x4014, 0x00);

            THEN("data from 0x0200 to 0x02FF should be copied to OAM")
            {
                for (auto i = 0xCC; i < OAM_SIZE; ++i)
                    REQUIRE(vram->readOAM(i) == 0xAA);
                for (auto i = 0; i < 0xCC; ++i)
                    REQUIRE(vram->readOAM(i) == 0xBB);
            }
        }
    }

    GIVEN("empty vram, ram and a ppu")
    {
        shared_ptr<DummyRenderer> renderer = make_shared<DummyRenderer>();
        shared_ptr<Memory> memory = make_shared<Memory>();
        shared_ptr<VRam> vram = make_shared<VRam>(HORIZONTAL);

        Ppu ppu(vram, memory, renderer);
        memory->subscribe(&ppu);

        WHEN("writing to PPUADDR register and PPUDATA")
        {
            memory->setAt(0x2006, 0x21);
            memory->setAt(0x2006, 0x08);

            memory->setAt(0x2007, 0xAA);


            THEN("data is set in the vram")
            {
                REQUIRE(vram->readMemory(0x2108) == 0xAA);
            }
        }
    }
}