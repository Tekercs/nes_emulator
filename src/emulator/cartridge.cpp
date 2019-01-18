#include "cartridge.h"

#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>

Emulator::Cartridge::Cartridge(const std::string &path)
{
    std::ifstream input(path, std::ios::binary);

    std::istream_iterator<uint8_t> iterator(input);
    std::cout << *iterator;
    ++iterator;
    std::cout << *iterator;
    ++iterator;
    std::cout << *iterator;
    ++iterator;
    std::cout << *iterator;
    ++iterator;
}
