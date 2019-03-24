#pragma once

#include <memory>

#include <Memory/Memory.h>
#include <Utils/Listener.h>

namespace Emulator::Utils
{
    enum Button { A = 7, B = 6, SELECT = 5, START = 4, UP = 3, DOWN = 2, LEFT = 1, RIGHT = 0};

    class Controller : public Listener
    {
    private:
        uint8_t pressedButtons;
        std::shared_ptr<Emulator::Memory::Memory> memory;

    public:
        Controller(std::shared_ptr<Emulator::Memory::Memory> memory);

        void notify(std::initializer_list<std::string> parameters) override;

        void press(Button button);
        void release(Button button);
    };

}