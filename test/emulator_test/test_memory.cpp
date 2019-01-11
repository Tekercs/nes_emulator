#include <catch.hpp>
#include <memory.h>
#include <iostream>

SCENARIO("when reading memory", "[Memory]")
{
    GIVEN("an empty memory")
    {
        auto * memory = new Emulator::Memory();

        WHEN("reading a valid address")
        {
            uint8_t value = memory->getFrom(0x00ff);

            THEN("result should be 0")
            {
                REQUIRE(value == 0);
            }
        }

        delete memory;
    }

    GIVEN("a memory with value 12 at 0x0012")
    {
        const uint16_t ADDRESS = 0x0012;
        const uint8_t VALUE = 12;

        auto * mem = new Emulator::Memory();
        mem->setAt(ADDRESS, VALUE);

        WHEN("memory accessed at 0x0012")
        {
            uint8_t value = mem->getFrom(ADDRESS);

            THEN("value 12 returned")
            {
                REQUIRE(value == VALUE);
            }
        }

        delete mem;
    }

    GIVEN("a memory with value 13 at 0x0000")
    {
        auto * mem = new Emulator::Memory();
        mem->setAt(0x0000, 13);

        WHEN("accessing memory at 0x0800 ")
        {
            uint8_t value = mem->getFrom(0x0800);

            THEN("value is 13")
            {
                REQUIRE(value == 13);
            }
        }

        delete mem;
    }

    GIVEN("empty memory")
    {
        auto * mem = new Emulator::Memory();

        WHEN("writing to mirrored memory position 0x0000")
        {
            mem->setAt(0x0000, 0x01);

            THEN("01 should appear 4 times in the memory")
            {
                auto totalAppearance = 0;
                for(auto i = 0; i < MEMORY_SIZE; ++i)
                {
                    if (mem->getFrom(i) == 0x01)
                        ++totalAppearance;
                }



                REQUIRE(totalAppearance == 4);
            }
        }

        delete mem;
    }
}
