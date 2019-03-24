#include "Controller.h"

#include <memory>

#include <Memory/Memory.h>

using namespace std;
using namespace Emulator::Utils;
using namespace Emulator::Memory;

Controller::Controller(shared_ptr<Memory::Memory> memory)
: pressedButtons(0)
, memory(move(memory))
, currentButton(START_BUTTON)
{ }

void Controller::notify(std::initializer_list<std::string> parameters)
{
    std::string eventName = *parameters.begin();
    std::string param1 = *(parameters.begin() +1);

    if (eventName == "memread" && param1 == "4016")
        this->writeCurrentButtonToMemory();
}

void Controller::press(Button button)
{
    this->pressedButtons = this->pressedButtons | (0b1 << button);
}

void Controller::release(Button button)
{
    this->pressedButtons = this->pressedButtons & (~(0b1 << button));
}

void Controller::writeCurrentButtonToMemory()
{
    this->memory->setAt(CONTROLLER_ADDRESS, (this->pressedButtons & (0b1 << this->currentButton)) >> this->currentButton);

    if (this->currentButton == RIGHT)
        this->currentButton = A;
    else
        --this->currentButton;
}
