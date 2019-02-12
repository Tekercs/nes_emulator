#pragma once

#include <cartridge.h>

void writeCartridgeToFile(const Emulator::ROM::Cartridge& cartridge, const std::string& path);
