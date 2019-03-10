#pragma once

#include <string>

namespace Emulator::Utils
{
    std::string convertIntToHexString(int number);
    int convertHexStringToInt(std::string hexString);
}
