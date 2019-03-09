#include "EventSource.h"

#include <initializer_list>

using namespace std;
using namespace Emulator::Utils;

void EventSource::subscribe(Listener* listener)
{
    this->listeners.insert(listener);
}

void EventSource::unsubscribe(Listener* listener)
{
    this->listeners.erase(listener);
}

void EventSource::notifyListeners(initializer_list<string> parameters)
{
    for (auto listener : this->listeners)
        listener->notify(parameters);
}