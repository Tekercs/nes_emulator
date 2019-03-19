#pragma once

#include <Ppu/Renderer.h>

class DummyRenderer : public Emulator::Ppu::Renderer
{
public:
    void colorPixel(Emulator::Ppu::Cords cords, Emulator::Ppu::Color color) override;

    void drawScreen() override;
};
