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
        bool isTrainerPresent;

        void readHeader(std::ifstream* file);
        void parseHeader();

    public:
        Cartridge(const std::string& path);
    };
}
