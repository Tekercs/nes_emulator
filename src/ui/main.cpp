#include <iostream>
#include <SDL2/SDL.h>

int main()
{
    SDL_Rect rect = {.x = 0, .y = 0, .w = 100, .h = 200};
    SDL_RenderPresent(renderer);

    SDL_Event event;
    auto quit = false;
    do
    {
        SDL_PollEvent(&event);

        quit = (event.type == SDL_QUIT);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    } while (!quit);



    return 0;
}
