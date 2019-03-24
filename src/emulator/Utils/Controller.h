#pragma once

#include <memory>

#include <Memory/Memory.h>
#include <Utils/Listener.h>

#define START_BUTTON       7
#define NUMBER_OF_BUTTONS  8
#define CONTROLLER_ADDRESS 0x4016

namespace Emulator::Utils
{
    enum Button { A = 7, B = 6, SELECT = 5, START = 4, UP = 3, DOWN = 2, LEFT = 1, RIGHT = 0};

    class Controller : public Listener
    {
    private:
        uint8_t pressedButtons;
        uint8_t currentButton;
        std::shared_ptr<Emulator::Memory::Memory> memory;

        void writeCurrentButtonToMemory();

    public:
        Controller(std::shared_ptr<Emulator::Memory::Memory> memory);

        void notify(std::initializer_list<std::string> parameters) override;

        void press(Button button);
        void release(Button button);
    };

}