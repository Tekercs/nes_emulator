#pragma once

#include <SDL2/SDL.h>

#include <Ppu/Ppu.h>

#define MAX_HORIZONTAL 256
#define MAX_VERTICAL   240

namespace Ui
{
    class GameWindow
    {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        uint8_t scaling;

    public:
        explicit GameWindow(uint8_t scaling);
        ~GameWindow();

        void colorPixel(Emulator::Ppu::Cords cords, Emulator::Ppu::Color color);
        void clearScreen();
    };
}
