#pragma once

#include <SDL2/SDL.h>

#include <Ppu/Ppu.h>
#include <Ppu/ColorPalette.h>
#include <Utils/Listener.h>
#include <Ppu/Renderer.h>

#define MAX_HORIZONTAL 256
#define MAX_VERTICAL   240

namespace Ui
{
    class GameWindow : public Emulator::Ppu::Renderer
    {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        uint8_t scaling;


    public:
        explicit GameWindow(uint8_t scaling);
        ~GameWindow();


        void colorPixel(Emulator::Ppu::Cords cords, Emulator::Ppu::Color color) override;

        void drawScreen() override;

        void clearScreen();
    };
}
