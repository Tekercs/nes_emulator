#include <catch.hpp>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

#include <Memory/Memory.h>
#include <Rom/Cartridge.h>
#include <Rom/Mapper.h>
#include <Cpu/Cpu.h>
#include <Cpu/Registers.h>

#include "helpers/TestCpuHelpers.h"

using namespace std;
using namespace Emulator::Cpu;
using namespace Emulator::Memory;
using namespace Emulator::ROM;

#define PATH_NESTEST "test/emulator_test/test_roms/kevtris/nestest.nes"
#define PATH_NESTEST_LOG "test/emulator_test/test_roms/kevtris/nestest.log"

SCENARIO("nestest.nes by kevtris")
{
    GIVEN("parsed and mapped nestest.nes and CPU PC at 0xC000")
    {
        shared_ptr<Memory> memory = make_shared<Memory>();
        shared_ptr<Registers> registers = make_shared<Registers>();
        registers->setProgramCounter(0xC000);
        registers->setStatusFlags(0x24);

        Cpu cpu(memory, registers);

        Cartridge cartridge(PATH_NESTEST);
        auto mapper = createMapper(cartridge, *memory.get());
        mapper->map();

        ifstream logFile(PATH_NESTEST_LOG);

        THEN("Running and checking same output after every cycle")
        {
            string logLine;
            string currentState;
            string prevLogLine;
            while(getline(logFile, logLine))
            {
                currentState = parseCurrentStateLog(*memory.get(), *registers.get());
                REQUIRE(logLine == currentState);
                prevLogLine = logLine;

                ++cpu;
            }
        }
    }
}
