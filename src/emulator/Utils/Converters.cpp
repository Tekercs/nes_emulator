#include "Converters.h"

#include <sstream>

using namespace std;
using namespace Emulator::Utils;

string Emulator::Utils::convertIntToHexString(int number)
{
    stringstream stream;
    stream << hex << number;

    return stream.str();
}

int Emulator::Utils::convertHexStringToInt(string hexString)
{
    stringstream stream;
    stream << hex << hexString;

    int result;
    stream >> result;

    return result;
}
