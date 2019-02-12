#pragma once

#include <string>

#define HEADER_STARTS 0
#define HEADER_LENGTH 16
#define TRAINER_LENGTH 512

/**
 * @namespace Emulator::ROM
 *
 * @brief This namespace groups code regarding the ROM emulation.
*/
namespace Emulator::ROM
{
    /**
     * @class Cartridge
     *
     * @brief This class represents a virtualized cartridge parser.
     *
     * @details The class capable to read and parse the NES2.0 (.nes)
     * file format, which is also backward compatible with the older
     * iNes (NES1.0) file format.
     */
    class Cartridge
    {
    private:

        /**
         * @var rawHeader
         *
         * @brief represent the raw unparsed header of the NES2.0 file
         *
         * @details The raw header is a 16 byte long binary sequence
         * which contains flags and size information about the given
         * cartridge.
         */
        uint8_t* rawHeader;

        /**
         * @var trainer
         *
         * @brief Trainer area section of the cartridge.
         *
         * @details This section is held for backward
         * compatibility reasons such as emulators and
         * other intrepters.
         */
        uint8_t* trainer;

        /**
         * @var prgRom
         *
         * @brief The actual program data of the game
         *
         * @details This array of 8 bit unsinged integers
         * holds the actual opcodes and it's parameters
         * which are the game code meant to be run on the
         * cpu.
         */
        uint8_t* prgRom;

        /**
         * @var chrRom
         *
         * @brief Sprite and graphics data of the game
         *
         * @details This array holds the sprite and color
         * palette information of all the graphics data of
         * the game.
         */
        uint8_t* chrRom;

        /**
         * @var miscRomSize
         *
         * @brief size of the miscRom
         *
         * @details Size of the miscRom calculated at file parsing.
         */
        uint32_t miscRomSize;

        /**
         * @var miscRom
         *
         * @brief additional rom data
         *
         * @details this is barely used only a few mapper
         * utilizes this rom type.
         */
        uint8_t* miscRom;

        /**
         * @var isTrainerPresent
         *
         * @brief indicates if cartridge contains trainer data
         *
         * @details this information is parsed out from the rawHeader
         * 6th byte's 3rd bit.
         *
         */
        bool isTrainerPresent;

        /**
         * @param file with .nes extension, opend in binary mode
         *
         * @brief This function read the rawHeader from the given file
         *
         * @details The raw header red out from the binary .nes file
         * which is the first 16 byte of the file. Always starts with
         * NES/n.
         */
        void readHeader(std::ifstream* file);

        /**
         * @brief parse the necessary bits and flags from rawHeader
         *
         * @details This function reads and turns the necessary
         * flags and bits of the rawHeader to easily readable ana
         * manageable classFields of Cartridge.
         */
        void parseHeader();

        /**
         * @param file with .nes extension, opend in binary mode
         *
         * @brief This function read the trainer rom from the file.
         *
         * @details Reads the fix 512 byte sized trainter rom
         * and populate the trainter field of Cartridge with it.
         * based on the isTrainterPresnet flag.
         */
        void readTrainer(std::ifstream* file);

        /**
         * @param file with .nes extension, opend in binary mode
         *
         * @brief this function read the program rom from the file.
         *
         * @details Reads the program rom which sized was determined
         * in the rawHeader. See calcPRGRomSize.
         * And populates the prgRom field of the Cartridge class
         * with the data.
         */
        void readPRGRom(std::ifstream* file);

        /**
         * @param file with .nes extension, opend in binary mode
         *
         * @brief This function reads the character rom from the file.
         *
         * @details The function reads the given sized character rom
         * See calcCHRRomSize. Then popululates the chrRom field of
         * the Cartridge class.
         */
        void readCHRRom(std::ifstream* file);

        /**
         * @param file with .nes extension, opend in binary mode
         *
         * @brief this function reads the misc rom data if presented.
         *
         * @details all Remainging data which left behind the chrRom
         * in the file belongs to the miscRom.
         */
        void readMiscRom(std::ifstream* file);


    public:
        /**
         * @param path to the .nes cartridge file.
         *
         * @brief opens the file with the given path and reads it.
         *
         * @details open the file at the given path in binary mode
         * and reads and populates the fields of this class with the
         * data.
         */
        Cartridge(const std::string& path);

        /**
         * @brief calculates the program rom size.
         *
         * @details Based on the rawHeader data calculates the program
         * rom size. Using the rawHeader 4th byte as LSB and
         * bits 0-3 of rawHeader 9th byte as MSB (12 bits in total).
         * If the 4 MSB bits are 1111 then using the exponent-multiplier
         * notation therefore size =
         *   1111 EEEE EEMM
         *        |||| ||++- Multiplier, actual value is MM*2+1 (1,3,5,7)
         *        ++++-++--- Exponent (2^E), 0-63
         * else:
         * BBBB BBBB BBBB
         * ++++-++++-++++- PRG-ROM size in 16 KiB units,
         *                 values $000-$EFF for 0..62,898,176 bytes
         *
         * @return the actual size of the prgRom in bytes.
         */
        uint32_t calcPRGRomSize() const;

        /**
         * @brief calculates the character rom size.
         *
         * @details Based on the rawHeader data calculates the program
         * rom size. Using the rawHeader 5th byte as LSB and
         * bits 4-7 of rawHeader 9th byte as MSB (12 bits in total).
         * If the 4 MSB bits are 1111 then using the exponent-multiplier
         * notation therefore size =
         *   1111 EEEE EEMM
         *        |||| ||++- Multiplier, actual value is MM*2+1 (1,3,5,7)
         *        ++++-++--- Exponent (2^E), 0-63
         * else:
         * BBBB BBBB BBBB
         * ++++-++++-++++- PRG-ROM size in 8 KiB units,
         *                 values $000-$EFF for 0..31,449,088 bytes
         *
         * @return the actual size of the chrRom in bytes.
         */
        uint32_t calcCHRRomSize() const;

        /**
         * @brief Accessor function for rawHeader field.
         *
         * @return pointer to the rawHeader field of the given Cartridge class.
         */
        uint8_t* getRawHeader() const;

        /**
         * @brief Accessor function for miscRom field.
         *
         * @return pointer to the miscRom field of the given Cartridge class.
         */
        uint8_t* getMiscRom() const;

        /**
         * @brief Accessor function for prgRom field.
         *
         * @return pointer to the prgRom field of the given Cartridge class.
         */
        uint8_t* getPrgRom() const;

        /**
         * @brief Accessor function for chrRom field.
         *
         * @return pointer to the chrRom field of the given Cartridge class.
         */
        uint8_t* getChrRom() const;

        /**
         * @brief Accessor function for trainer field.
         *
         * @return pointer to trainer field of the given Cartridge class.
         */
        uint8_t* getTrainer() const;

        /**
         * @brief Accessor function for miscRomSize.
         *
         * @return returns the size of the miscRom as a 32bit unsigned integer.
         */
        uint32_t getMiscRomSize() const;

        /**
         * @brief Accessor function for isTrainerPresent
         *
         * @return bool value based on if the trainer area present in the Cartridge;
         */
        bool trainerExists() const;

    };
}
