#include "Controller.h"

using namespace Emulator::Utils;

Controller::Controller()
: pressedButtons(0)
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
