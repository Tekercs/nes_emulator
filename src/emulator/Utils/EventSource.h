#pragma once

#include <set>
#include <initializer_list>

#include <Utils/Listener.h>

namespace Emulator::Utils
{
    class EventSource 
    {
    protected:
        std::set<Listener*> listeners;

    public:
        void subscribe(Listener* listener);
        void unsubscribe(Listener* listener);

        void notifyListeners (std::initializer_list<std::string> parameters);
    };
}