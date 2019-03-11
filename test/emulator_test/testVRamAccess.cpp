#include <catch.hpp>

#include <string>
#include <memory>
#include <vector>

#include <Ppu/VRam.h>
#include <Ppu/Ppu.h>
#include <Memory/Memory.h>

using namespace std;
using namespace Emulator::Ppu;
using namespace Emulator::Memory;

SCENARIO("accessing vram via memory mappings")
{
    GIVEN("empty memory, vram and inited PPU")
    {
        shared_ptr<Memory> memory = make_shared<Memory>();
        shared_ptr<VRam> vram = make_shared<VRam>();

        Ppu ppu(vram, memory);

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

            THEN("write once more to the OAMADDR and check if owerriten")
            {
                memory->setAt(0x2004, 0x06);
                REQUIRE((vram->readOAM(0x02)) == 0x06);
            }
        }
    }
}