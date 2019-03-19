#include "GameWindow.h"

#include <SDL2/SDL.h>

using namespace Ui;
using namespace Emulator::Ppu;

GameWindow::GameWindow(uint8_t scaling) : scaling(scaling)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    this->window = SDL_CreateWindow("first sdl"
            , SDL_WINDOWPOS_UNDEFINED
            , SDL_WINDOWPOS_UNDEFINED
            , MAX_HORIZONTAL * this->scaling
            , MAX_VERTICAL * this->scaling
            , SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(window, -1, 0);

    this->clearScreen();
}

void GameWindow::colorPixel(Cords cords, Color color)
{
    SDL_Rect rect = {
            .x = cords.horizontal * this->scaling,
            .y = cords.vertical * this->scaling,
            .w = this->scaling,
            .h = this->scaling
    };
    SDL_SetRenderDrawColor(this->renderer,
            color.red,
            color.green,
            color.blue,
            color.alpha);
    SDL_RenderFillRect(this->renderer, &rect);

}

void GameWindow::clearScreen()
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);

    SDL_RenderPresent(this->renderer);
}

GameWindow::~GameWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameWindow::drawScreen()
{
    SDL_RenderPresent(this->renderer);
}
