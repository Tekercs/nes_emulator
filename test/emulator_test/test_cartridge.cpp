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

            tempOut.write(reinterpret_cast<const char *>(cartridge1.getRawHeader()), HEADER_LENGTH);

            if (cartridge1.trainerExists())
                tempOut.write(reinterpret_cast<const char *>(cartridge1.getTrainer()), TRAINER_LENGTH);

            tempOut.write(reinterpret_cast<const char *>(cartridge1.getPrgRom()), cartridge1.calcPRGRomSize());
            tempOut.write(reinterpret_cast<const char *>(cartridge1.getChrRom()), cartridge1.calcCHRRomSize());
            tempOut.write(reinterpret_cast<const char *>(cartridge1.getMiscRom()), cartridge1.getMiscRomSize());

            tempOut.close();

            Cartridge cartridge2(tempFileName);


        }
    }
}