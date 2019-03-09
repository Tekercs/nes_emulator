#pragma once

#include <initializer_list>
#include <string>

namespace Emulator::Utils
{
    class Listener
    {
    public:
        virtual void notify(std::initializer_list<std::string> parameters) = 0;
    };
} 