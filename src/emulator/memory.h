#pragma once
#include <cstdint>

#define MEMORY_SIZE 65535
#define MEM_FIRST 0x0000
#define MEM_LAST 0xFFFF

namespace Emulator
{
    class Memory 
    {
    private:
        uint8_t memory[MEMORY_SIZE];
        
    public:
        Memory();
        
        void setMemoryAt(uint16_t address, uint8_t value);
        uint8_t getMemoryFrom(uint16_t address);
    };
}
