#pragma once
#include <cstdint>

#define MEMORY_SIZE         0x10000
#define ZEROPAGE            0x0000
#define STACK               0x0100
#define RAM                 0x0200
#define RAM_MIRROR          0x0800

#define IO_REGISTERS        0x2000
#define IO_REGISTERS_SIZE   8
#define IO_REGISTERS_MIRROR 0x2008
#define IO_REGISTERS_SEC    0x4000

#define EXP_ROM             0x4020
#define SRAM                0x6000
#define PRG_LOWER           0x8000
#define PRG_UPPER           0xC000

/**
 * @namespace Emulator
 *
 * @brief This namespace groups emulator classes.
 */
namespace Emulator
{

    /**
     * @class Memory
     *
     * @brief NES Memory module representation.
     *
     * @details This class represents the NES' Memory
     * module including it's mirroring properties
     * based on the specification.
     */
    class Memory
    {
    private:
        uint8_t* memory[MEMORY_SIZE];

        void generateRAM();
        void generateIORegisters();

    public:

        /**
         * @brief Constructor for Memory object
         *
         * @details Creates an empty Memory emulation object
         * with preconfigured memory mirroring based on the
         * NES system specification.
         */
        Memory();

        /**
         * @brief Set accessor function for memory slots.
         *
         * @param address for the target memory location
         * @param value for the given address to write
         *
         * @details Write the passed 8 bit long unsigned integer
         * value to the given memory address which represented
         * with 16 bit unsigned integer value.
         */
        void setAt(uint16_t address, uint8_t value);

        /**
         * @brief Get accessor function for memory slots.
         *
         * @param address for the target memory location
         * @return the stored value at address
         *
         * @details Return the 8 Bit unsinged integer value
         * which is stored at the address (16 bit unsgined integer) location in
         * the memory
         */
        uint8_t getFrom(uint16_t address);
    };
}
