//
// Created by bence on 24/03/19.
//

#include "Controller.h"

void Emulator::Utils::Controller::notify(std::initializer_list<std::string> parameters)
{
    std::string eventName = *parameters.begin();
    std::string param1 = "";

    if (eventName == "memread" && param1 == "4016")
    {
        // handle controller access
    }
}
