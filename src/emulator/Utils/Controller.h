#pragma once

#include <Utils/Listener.h>

namespace Emulator::Utils
{
    class Controller : public Listener
    {

    public:
        void notify(std::initializer_list<std::string> parameters) override;
    };
}