#pragma once

#include <string>

#define HEADER_STARTS 0
#define HEADER_LENGTH 16
#define TRAINER_LENGTH 512

namespace Emulator
{
    class Cartridge
    {
    private:
        uint8_t rawHeader[HEADER_LENGTH];
        uint8_t trainer[TRAINER_LENGTH];
        uint8_t* prgRom;
        bool isTrainerPresent;

        void readHeader(std::ifstream* file);
        void readTrainer(std::ifstream* file);
        void readPRGRom(std::ifstream* file);
        void parseHeader();

        uint32_t calcPRGRomSize();

    public:
        Cartridge(const std::string& path);
    };
}
