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
#include <Utils/Controller.h>

using namespace std;
using namespace Ui;
using namespace Emulator::Cpu;
using namespace Emulator::ROM;
using namespace Emulator::Ppu;
using namespace Emulator::Utils;
using namespace Emulator::Memory;
using namespace std::chrono;
using namespace std::this_thread;

int main(int argc, char *argv[])
{
    Cartridge cartridge(argv[1]);

    shared_ptr<VRam> vram = make_shared<VRam>(cartridge.getNametableMirroring());
    shared_ptr<Memory> memory = make_shared<Memory>();
    shared_ptr<Registers> registers = make_shared<Registers>();
    shared_ptr<Controller> controller = make_shared<Controller>(memory);

    shared_ptr<GameWindow> gameWindow = make_shared<GameWindow>(2, controller);

    Cpu cpu(memory, registers);
    Ppu ppu(vram, memory, gameWindow);

    auto mapper = createMapper(cartridge, *memory.get(), *vram.get());
    mapper->map();

    cpu.reset();

    cpu.subscribe(&ppu);
    ppu.subscribe(&cpu);
    memory->subscribe(&ppu);
    memory->subscribe(controller.get());

    do
    {
        gameWindow->pollEvent();
        ++cpu;
    }while(!gameWindow->isClosed());

    return 0;

}
