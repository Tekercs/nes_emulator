#include <memory>
#include <SDL2/SDL.h>

#include <GameWindow.h>

#include <Ppu/VRam.h>
#include <Ppu/Ppu.h>
#include <Memory/Memory.h>
#include <Cpu/Registers.h>
#include <Cpu/Cpu.h>
#include <Rom/Cartridge.h>
#include <Rom/Mapper.h>

using namespace std;
using namespace Ui;
using namespace Emulator::Cpu;
using namespace Emulator::ROM;
using namespace Emulator::Ppu;
using namespace Emulator::Memory;

int main()
{
    shared_ptr<Memory> memory = make_shared<Memory>();
    shared_ptr<Registers> registers = make_shared<Registers>();
    shared_ptr<VRam> vram = make_shared<VRam>(HORIZONTAL);

    registers->setProgramCounter(0xC000);
    registers->setStatusFlags(0x24);

    Cpu cpu(memory, registers);
    Ppu ppu(vram, memory);

    Cartridge cartridge("/home/bence/Desktop/ballon_fight.nes");
    auto mapper = createMapper(cartridge, *memory.get(), *vram.get());
    mapper->map();

    registers->setProgramCounter((memory->getFrom(RESET_UPPER) << 8) + memory->getFrom(RESET_LOWER));

    GameWindow gameWindow(4);
    gameWindow.colorPixel({.horizontal = 1, .vertical = 2}, {.red = 255, .green = 255, .blue = 0, .alpha = 0});

    while(true)
        ++cpu;

    SDL_Delay(5000);

    return 0;
}
