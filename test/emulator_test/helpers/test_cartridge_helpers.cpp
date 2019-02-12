#include "test_cartridge_helpers.h"

#include <fstream>

using namespace std;

void writeCartridgeToFile(const Emulator::ROM::Cartridge& cartridge1, const std::string& path)
{
    ofstream tempOut(path, ios::binary);

    tempOut.write(reinterpret_cast<const char *>(cartridge1.getRawHeader()), HEADER_LENGTH);

    if (cartridge1.trainerExists())
        tempOut.write(reinterpret_cast<const char *>(cartridge1.getTrainer()), TRAINER_LENGTH);

    tempOut.write(reinterpret_cast<const char *>(cartridge1.getPrgRom()), cartridge1.calcPRGRomSize());
    tempOut.write(reinterpret_cast<const char *>(cartridge1.getChrRom()), cartridge1.calcCHRRomSize());
    tempOut.write(reinterpret_cast<const char *>(cartridge1.getMiscRom()), cartridge1.getMiscRomSize());

    tempOut.close();
}
