#include <catch.hpp>
#include <memory.h>

SCENARIO("when reading memory", "[Memory]")
{
    GIVEN("an empty memory")
    {
        Emulator::Memory* memory = new Emulator::Memory();
        
        WHEN("reading a valid address")
        {
            uint8_t value = memory->getMemoryFrom(0x00ff);
            
            THEN("result should be 0")
            {
                REQUIRE(value == 0);
            }
        }
    }
}
