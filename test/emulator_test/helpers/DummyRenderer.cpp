#include "DummyRenderer.h"

#include <iostream>

using namespace std;
using namespace Emulator::Ppu;

void DummyRenderer::colorPixel(Cords cords, Color color)
{
    cout << "x: " << cords.horizontal << " y:" << cords.vertical << endl;
    cout << "r: " << color.red << " g:" << color.green << " b:" << color.blue << endl;
}

void DummyRenderer::drawScreen()
{
    cout << "screen rendere" << endl;
}

void DummyRenderer::clearScreen(Color color)
{
    cout << "clear screen" << endl;
}
