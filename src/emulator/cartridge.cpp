#include "cartridge.h"

#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>

Emulator::Cartridge::Cartridge(const std::string &path)
{
    std::ifstream input(path, std::ios::binary);

    std::istream_iterator<uint8_t> iterator(input);

    // read the header
    uint8_t header[HEADER_LENGTH];
    for (uint8_t &i : header)
    {
        i = *iterator;
        ++iterator;
    }

    bool isTrainerPresented = ((header[6] & 0x04 ) > 0);
    if (isTrainerPresented)
    {
        uint8_t trainer[TRAINER_LENGTH];
        for (uint8_t &i : trainer)
        {
            i = *iterator;
            ++iterator;
        }
    }
}
