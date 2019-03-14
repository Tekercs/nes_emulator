#include "GameWindow.h"

#include <SDL2/SDL.h>

Ui::GameWindow::GameWindow(uint8_t scaling) : scaling(scaling)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    this->window = SDL_CreateWindow("first sdl"
            , SDL_WINDOWPOS_UNDEFINED
            , SDL_WINDOWPOS_UNDEFINED
            , MAX_HORIZONTAL * this->scaling
            , MAX_VERTICAL * this->scaling
            , SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(window, -1, 0);
}

void Ui::GameWindow::colorPixel(Ui::Cords cords, Ui::Color color)
{

}

void Ui::GameWindow::clearScreen()
{

}

Ui::GameWindow::~GameWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
