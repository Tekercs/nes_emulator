#include <catch.hpp>
#include <fstream>
#include <cstdio>
#include <iostream>

#include <Rom/cartridge.h>

using namespace std;
using namespace Emulator::ROM;

SCENARIO("reading cartridges from given file")
{
    string path = "../../../test/emulator_test/test_roms/blargg/02-implied.nes";

    GIVEN("parsed nrom .nes file into a Cartrdige type saved in a temporary file")
    {
        Cartridge cartridge1(path);
        string tempFileName = tmpnam(nullptr);

        ofstream tempOut(tempFileName, ios::binary);

        tempOut.write(reinterpret_cast<const char *>(cartridge1.getRawHeader()), HEADER_LENGTH);

        if (cartridge1.trainerExists())
            tempOut.write(reinterpret_cast<const char *>(cartridge1.getTrainer()), TRAINER_LENGTH);

        tempOut.write(reinterpret_cast<const char *>(cartridge1.getPrgRom()), cartridge1.calcPRGRomSize());
        tempOut.write(reinterpret_cast<const char *>(cartridge1.getChrRom()), cartridge1.calcCHRRomSize());
        tempOut.write(reinterpret_cast<const char *>(cartridge1.getMiscRom()), cartridge1.getMiscRomSize());

        tempOut.close();

        THEN ("check if two .nes file equals")
        {
            ifstream input(path, ios::binary);
            ifstream tempInput(tempFileName, ios::binary);

            input.seekg(0, ifstream::end);
            auto inputLength = input.tellg();
            input.seekg(0, ifstream::beg);

            tempInput.seekg(0, ifstream::end);
            auto tempInputLength = tempInput.tellg();
            tempInput.seekg(0, ifstream::beg);

            REQUIRE(inputLength == tempInputLength);

            istreambuf_iterator<char> iterator(input);
            istreambuf_iterator<char> tempIterator(tempInput);

            char inputRead, tempInputRead;
            for (auto i = 0; i < inputLength; ++i)
            {
                inputRead = *iterator;
                tempInputRead = *tempIterator;

                REQUIRE(inputRead == tempInputRead);

                ++iterator;
                ++tempIterator;
            }

            input.close();
            tempInput.close();
        }

        THEN("check if equal")
        {
            Cartridge cartridge2(tempFileName);

            uint32_t i;
            for (i = 0; i < HEADER_LENGTH; ++i)
                REQUIRE(cartridge1.getRawHeader()[i] == cartridge1.getRawHeader()[i]);

            REQUIRE(cartridge1.trainerExists() == cartridge2.trainerExists());
            if (cartridge1.trainerExists() && cartridge1.trainerExists() == cartridge2.trainerExists())
                for (i = 0; i < TRAINER_LENGTH; ++i)
                    REQUIRE(cartridge1.getTrainer()[i] == cartridge1.getTrainer()[i]);

            for (i = 0; i < cartridge1.calcPRGRomSize(); ++i)
                REQUIRE(cartridge1.getPrgRom()[i] == cartridge1.getPrgRom()[i]);

            for (i = 0; i < cartridge1.calcCHRRomSize(); ++i)
                REQUIRE(cartridge1.getChrRom()[i] == cartridge1.getChrRom()[i]);

            REQUIRE(cartridge1.getMiscRomSize() == cartridge2.getMiscRomSize());

            for (i = 0; i < cartridge1.getMiscRomSize(); ++i)
                REQUIRE(cartridge1.getMiscRom()[i] == cartridge1.getMiscRom()[i]);
        }
    }
}