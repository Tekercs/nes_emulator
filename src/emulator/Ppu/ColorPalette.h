#pragma once

#include <cstdint>

namespace Emulator::Ppu
{
    struct Color
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    };

    const Color colors[] =
        {
            {.red = 124, .green = 124, .blue = 124, .alpha = 0},
            {.red = 0, .green = 0, .blue = 252, .alpha = 0},
            {.red = 0, .green = 0, .blue = 188, .alpha = 0},
            {.red = 68, .green = 40, .blue = 188, .alpha = 0},
            {.red = 148, .green = 0, .blue = 132, .alpha = 0},
            {.red = 168, .green = 0, .blue = 32, .alpha = 0},
            {.red = 168, .green = 1, .blue = 60, .alpha = 0},
            {.red = 136, .green = 2, .blue = 00, .alpha = 0},
            {.red = 80, .green = 4, .blue = 80, .alpha = 0},
            {.red = 0, .green = 12, .blue = 00, .alpha = 0},
            {.red = 0, .green = 10, .blue = 40, .alpha = 0},
            {.red = 0, .green = 8, .blue = 80, .alpha = 0},
            {.red = 0, .green = 64, .blue = 88, .alpha = 0},
            {.red = 0, .green = 0, . blue = 0, .alpha = 0},
            {.red = 0, .green = 0, .blue = 0, .alpha = 0},
            {.red = 0, .green = 0, .blue = 0, .alpha = 0},
            {.red = 188, .green = 188, .blue = 188, .alpha = 0},
            {.red = 0, .green = 120, .blue = 248, .alpha = 0},
            {.red = 0, .green = 88, .blue = 248, .alpha = 0},
            {.red = 104, .green = 68, .blue = 252, .alpha = 0},
            {.red = 216, .green = 0, .blue = 204, .alpha = 0},
            {.red = 228, .green = 0, .blue = 88, .alpha = 0},
            {.red = 248, .green = 5, .blue = 60, .alpha = 0},
            {.red = 228, .green = 92, .blue = 16, .alpha = 0},
            {.red = 172, .green = 12, .blue = 40, .alpha = 0},
            {.red = 0, .green = 18, .blue = 40, .alpha = 0},
            {.red = 0, .green = 16, .blue = 80, .alpha = 0},
            {.red = 0, .green = 168, .blue = 68, .alpha = 0},
            {.red = 0, .green = 136, .blue = 136, .alpha = 0},
            {.red = 0, .green = 0, .blue = 0, .alpha = 0},
            {.red = 0, .green = 0, .blue = 0, .alpha = 0},
            {.red = 0, .green = 0, .blue = 0, .alpha = 0},
            {.red = 248, .green = 248, .blue = 248, .alpha = 0},
            {.red = 60, .green = 188, .blue = 252, .alpha = 0},
            {.red = 104, .green = 136, .blue = 252, .alpha = 0},
            {.red = 152, .green = 120, .blue = 248, .alpha = 0},
            {.red = 248, .green = 120, .blue = 248, .alpha = 0},
            {.red = 248, .green = 88, .blue = 152, .alpha = 0},
            {.red = 248, .green = 120, .blue = 88, .alpha = 0},
            {.red = 252, .green = 160, .blue = 68, .alpha = 0},
            {.red = 248, .green = 18, .blue = 40, .alpha = 0},
            {.red = 184, .green = 248, .blue = 24, .alpha = 0},
            {.red = 88, .green = 216, .blue = 84, .alpha = 0},
            {.red = 88, .green = 248, .blue = 152, .alpha = 0},
            {.red = 0, .green = 232, .blue = 216, .alpha = 0},
            {.red = 120, .green = 120, .blue = 120, .alpha = 0},
            {.red = 0, .green = 0, .blue = 0, .alpha = 0},
            {.red = 0, .green = 0, .blue = 0, .alpha = 0},
            {.red = 252, .green = 252, .blue = 252, .alpha = 0},
            {.red = 164, .green = 228, .blue = 252, .alpha = 0},
            {.red = 184, .green = 184, .blue = 248, .alpha = 0},
            {.red = 216, .green = 184, .blue = 248, .alpha = 0},
            {.red = 248, .green = 184, .blue = 248, .alpha = 0},
            {.red = 248, .green = 164, .blue = 192, .alpha = 0},
            {.red = 240, .green = 208, .blue = 176, .alpha = 0},
            {.red = 252, .green = 224, .blue = 168, .alpha = 0},
            {.red = 248, .green = 216, .blue = 120, .alpha = 0},
            {.red = 216, .green = 248, .blue = 120, .alpha = 0},
            {.red = 184, .green = 248, .blue = 184, .alpha = 0},
            {.red = 184, .green = 248, .blue = 216, .alpha = 0},
            {.red = 0, .green = 252, .blue = 252, .alpha = 0},
            {.red = 248, .green = 216, .blue = 248, .alpha = 0},
            {.red = 0, .green = 0, .blue = 0, .alpha = 0},
            {.red = 0, .green = 0, .blue = 0, .alpha = 0}
        };
}
