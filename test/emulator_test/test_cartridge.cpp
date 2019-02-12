#include <catch.hpp>
#include <fstream>
#include <cstdio>

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

            auto trainer  = cartridge1.getTrainer();
            tempOut.write(reinterpret_cast<const char *>(trainer), TRAINER_LENGTH);

            auto prgRom = cartridge1.getPrgRom();
            tempOut.write(reinterpret_cast<const char *>(prgRom), cartridge1.calcPRGRomSize());

            auto chrRom = cartridge1.getChrRom();
            tempOut.write(reinterpret_cast<const char *>(chrRom), cartridge1.calcCHRRomSize());

            auto miscRom = cartridge1.getMiscRom();
            tempOut.write(reinterpret_cast<const char *>(miscRom), cartridge1.getMiscRomSize());

            tempOut.close();
        }
    }
}