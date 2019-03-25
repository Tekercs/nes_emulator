#pragma once

#include <memory>
#include <SDL2/SDL.h>

#include <Ppu/Ppu.h>
#include <Ppu/ColorPalette.h>
#include <Utils/Listener.h>
#include <Utils/Controller.h>
#include <Ppu/Renderer.h>

#define MAX_HORIZONTAL 256
#define MAX_VERTICAL   240

namespace Ui
{
    class GameWindow : public Emulator::Ppu::Renderer
    {
    private:
        std::shared_ptr<Emulator::Utils::Controller> controller;
        SDL_Window* window;
        SDL_Renderer* renderer;
        uint8_t scaling;
        bool close;


        Emulator::Utils::Button convertSDLKeyToEmulatorKey(SDL_Keycode sdlKeycode);

    public:
        explicit GameWindow(uint8_t scaling, std::shared_ptr<Emulator::Utils::Controller> controller);
        ~GameWindow();


        void colorPixel(Emulator::Ppu::Cords cords, Emulator::Ppu::Color color) override;

        void drawScreen() override;

        void clearScreen(Emulator::Ppu::Color color) override;

        void pollEvent();

        bool isClosed();

    };
}
