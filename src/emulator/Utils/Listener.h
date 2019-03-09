#pragma once

#include <initializer_list>

namespace Emulator::Utils
{
    class Listener
    {
    public: 

        template<class T>
        void operator() (T event);
    };
} 