#include "Ppu.h"

#include <iostream>

using namespace std;
using namespace Emulator::Ppu;

Ppu::Ppu(std::shared_ptr<VRam> vram, std::shared_ptr<Emulator::Memory::Memory> memory)
: memory(std::move(memory))
, vram(std::move(vram))
{
    this->oamAccessor.adress = 0;
    this->oamAccessor.value = 0;
}

void Ppu::notify(initializer_list<string> parameters)
{
    cout << "eddki" << endl;
}