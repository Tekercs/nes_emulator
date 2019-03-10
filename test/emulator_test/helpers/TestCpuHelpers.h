#pragma once

#include <string>

#include <Memory/Memory.h>
#include <Cpu/Registers.h>

std::string parseCurrentStateLog(Emulator::Memory::Memory& memory, const Emulator::Cpu::Registers& registers);
