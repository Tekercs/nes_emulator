#include <catch.hpp>
#include <fstream>
#include <cstdio>
#include <iostream>

#include <cartridge.h>

using namespace std;
using namespace Emulator::ROM;

SCENARIO("reading cartridges from given file")
{
    string path = "../../../test/emulator_test/test_roms/blargg/02-implied.nes";

    GIVEN("parsed nrom .nes file into a Cartrdige type and a temporary file")
    {
        Cartridge cartridge1(path);
        string tempFileName = tmpnam(nullptr);

        THEN("save and reread check if equal")
        {
            ofstream tempOut(tempFileName, ios::binary);

            auto rawHeader = cartridge1.getRawHeader();
            tempOut.write(reinterpret_cast<const char *>(rawHeader), HEADER_LENGTH);

            tempOut.close();
        }
    }
}