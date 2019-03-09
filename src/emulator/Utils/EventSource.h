#pragma once

#include <set>
#include <initializer_list>

#include <Utils/Listener.h>

namespace Emulator::Utils
{
    class EventSource 
    {
    private:
        std::set<Listener*> listeners;

    public:
        EventSource& operator += (Listener* listener);
        EventSource& operator -= (Listener* listener);

        template<class T>
        void operator() (T event);
    };
}