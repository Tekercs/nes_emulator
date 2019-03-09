#include "EventSource.h"

using namespace std;
using namespace Emulator::Utils;


EventSource& EventSource::operator += (Listener* listener)
{
    return *this;
}

EventSource& EventSource::operator -= (Listener* listener)
{
    return *this;
}

template <class T>
void EventSource::operator() (T event)
{

}