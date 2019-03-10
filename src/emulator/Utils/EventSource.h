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
        bool isTriggerBlocked = false;

    public:
        void subscribe(Listener* listener);
        void unsubscribe(Listener* listener);

        void notifyListeners (std::initializer_list<std::string> parameters);
    };
}