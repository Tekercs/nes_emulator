#pragma once

#include <string>

#define HEADER_LENGTH 16
#define TRAINER_LENGTH 512

namespace Emulator
{
    class Cartridge
    {
    public:
        Cartridge(const std::string& path);
    };
}
