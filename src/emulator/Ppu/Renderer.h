#pragma once

#include <Ppu/ColorPalette.h>

namespace Emulator::Ppu
{
    struct Cords
    {
        uint16_t horizontal;
        uint16_t vertical;
    };

    class Renderer
    {
    public:
        virtual void colorPixel(Cords cords, Color color) = 0;
        virtual void drawScreen() = 0;
    };
}
