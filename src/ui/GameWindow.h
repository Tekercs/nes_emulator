#pragma once

#include <SDL2/SDL.h>

#define MAX_HORIZONTAL 256
#define MAX_VERTICAL   240

namespace Ui
{
    struct Cords
    {
        uint16_t horizontal;
        uint16_t vertical;
    };

    struct Color
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    class GameWindow
    {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        uint8_t scaling;

    public:
        explicit GameWindow(uint8_t scaling);
        ~GameWindow();

        void colorPixel(Cords cords, Color color);
        void clearScreen();
    };
}
