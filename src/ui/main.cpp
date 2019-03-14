#include <iostream>
#include <SDL2/SDL.h>

#include <GameWindow.h>

using namespace std;
using namespace Ui;

int main()
{
    GameWindow gameWindow(4);
    gameWindow.colorPixel({.horizontal = 1, .vertical = 2}, {.red = 255, .green = 255, .blue = 0, .alpha = 0});

    SDL_Delay(5000);

    return 0;
}
