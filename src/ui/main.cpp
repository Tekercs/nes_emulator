#include <memory>
#include <SDL2/SDL.h>
#include <chrono>
#include <thread>

#include <GameWindow.h>

#include <Ppu/VRam.h>
#include <Ppu/Ppu.h>
#include <Memory/Memory.h>
#include <Cpu/Registers.h>
#include <Cpu/Cpu.h>
#include <Rom/Cartridge.h>
#include <Rom/Mapper.h>
#include <Utils/Converters.h>

using namespace std;
using namespace Ui;
using namespace Emulator::Cpu;
using namespace Emulator::ROM;
using namespace Emulator::Ppu;
using namespace Emulator::Memory;
using namespace std::chrono;
using namespace std::this_thread;

int main()
{
    shared_ptr<Memory> memory = make_shared<Memory>();
    shared_ptr<Registers> registers = make_shared<Registers>();
    shared_ptr<VRam> vram = make_shared<VRam>(HORIZONTAL);

    registers->setProgramCounter(0xC000);
    registers->setStatusFlags(0x24);

    shared_ptr<GameWindow> gameWindow = make_shared<GameWindow>(2);

    Cpu cpu(memory, registers);
    Ppu ppu(vram, memory, gameWindow);

    Cartridge cartridge("/home/bence/Desktop/ballon_fight.nes");
    //Cartridge cartridge("/home/bence/Workspace/nes_emulator/test/emulator_test/test_roms/rainwarrior/color_test.nes");
    //Cartridge cartridge("/home/bence/Workspace/nes_emulator/test/emulator_test/test_roms/kevtris/nestest.nes");
    auto mapper = createMapper(cartridge, *memory.get(), *vram.get());
    mapper->map();

    cpu.reset();

    cpu.subscribe(&ppu);
    ppu.subscribe(&cpu);
    memory.get()->subscribe(&ppu);


    while(true)
    {
        ++cpu;
        sleep_for(nanoseconds(6));
    }


    return 0;
}
