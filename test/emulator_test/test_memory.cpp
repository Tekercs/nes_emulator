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
        
        delete memory;
    }
    
    GIVEN("a memory with value 12 at 0x0012")
    {
        const uint16_t ADDRESS = 0x0012;
        const uint8_t VALUE = 12;
        
        Emulator::Memory* mem = new Emulator::Memory();
        mem->setMemoryAt(ADDRESS, VALUE);
        
        WHEN("memory accessed at 0x0012")
        {
            uint8_t value = mem->getMemoryFrom(ADDRESS);
            
            THEN("value 12 returned")
            {
                REQUIRE(value == VALUE);
            }
        }
    }
}
