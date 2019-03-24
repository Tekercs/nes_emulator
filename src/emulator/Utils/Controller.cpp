#include "Controller.h"

#include <memory>

#include <Memory/Memory.h>

using namespace std;
using namespace Emulator::Utils;
using namespace Emulator::Memory;

Controller::Controller(shared_ptr<Memory::Memory> memory)
: pressedButtons(0)
, memory(move(memory))
{ }

void Controller::notify(std::initializer_list<std::string> parameters)
{
    std::string eventName = *parameters.begin();
    std::string param1 = "";

    if (eventName == "memread" && param1 == "4016")
    {
        // handle controller access
    }
}

void Controller::press(Button button)
{
    this->pressedButtons = this->pressedButtons | (0b1 << button);
}

void Controller::release(Button button)
{
    this->pressedButtons = this->pressedButtons & (~(0b1 << button));
}
