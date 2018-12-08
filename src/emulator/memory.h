#pragma once
#include <cstdint>

#define MEMORY_SIZE 0x10000

namespace Emulator
{
    class Memory 
    {
    private:
        uint8_t memory[MEMORY_SIZE];
        
    public:
        Memory();
        
        void setAt(uint16_t address, uint8_t value);
        uint8_t getFrom(uint16_t address);
    };
}
