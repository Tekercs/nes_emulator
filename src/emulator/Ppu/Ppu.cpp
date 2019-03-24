#include "Ppu.h"

#include <Utils/Converters.h>
#include <Ppu/ColorPalette.h>
#include <iostream>

using namespace std;
using namespace Emulator::Ppu;
using namespace Emulator::Utils;

Ppu::Ppu(shared_ptr<VRam> vram, shared_ptr<Emulator::Memory::Memory> memory, shared_ptr<Renderer> renderer)
: memory(move(memory))
, vram(move(vram))
, renderer(move(renderer))
, warmupCycles(WARMUP_CYCLES)
, cycleCounter(0)
, oamAddress(0)
, memoryAddress({.nextPart = HIGH_BYTE, .address = 0, .readBuffer = 0})
, controlFlags(DEFAULT_PPUCNTRL)
, statusFlags(DEFAULT_STATUS)
, outputMaskFlags(DEFAULT_MASKFLAGS)
{ }

uint8_t Ppu::getVramAddressIncrement()
{
    return (this->controlFlags & INCREMENT_BIT)? 1 : 32;
}

void Ppu::notify(initializer_list<string> parameters)
{
    std::string eventName = *parameters.begin();
    std::string param1 = "";
    std::string param2 = "";

    if (parameters.size() > 1)
        param1 = *(parameters.begin() + 1);

    if (parameters.size() > 2)
        param2 = *(parameters.begin() + 2);

    if (eventName == "memwrite" && (param1) == "2003")
    {
        this->setOAMAddress(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memwrite" && (param1) == "2004")
    {
        this->writeOAM(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memwrite" && (param1) == "4014")
    {
        this->triggerDMA((convertHexStringToInt((param2))) << 8);
        return;
    }

    if (eventName == "memwrite" && (param1) == "2006")
    {
        this->setMemoryAddress(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memwrite" && (param1) == "2007")
    {
        this->writeMemory(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memread" && (param1) == "2007")
    {
        this->readMemory();
        return;
    }

    if (eventName == "memwrite" && (param1) == "2000")
    {
        this->updateControlFlags(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memread" && (param1) == "2004")
    {
        this->readOAM();
        return;
    }

    if (eventName == "memwrite" && (param1) == "2001")
    {
        this->setOutputMaskFlags(convertHexStringToInt(param2));
        return;
    }

    if (eventName == "memread" && (param1) == "2002")
    {
        this->writeStatusToMemory();
        return;
    }

    if (eventName == "cyclepassed")
    {
        auto cyclesPassed = convertHexStringToInt(param1);
        for (uint8_t i = 0; i < cyclesPassed * 3; ++i)
            ++(*this);

        return;
    }
}

void Ppu::operator++()
{
    if (this->warmupCycles == 0)
    {
        if (this->cycleCounter == 0)
            this->unsetVblankStatusFlag();

        if (this->cycleCounter == RENDER_FINISH)
        {
            Color backgroundColor = colors[this->vram->readMemory(UNIVERSAL_BG_COLOR)];
            this->renderer->clearScreen(backgroundColor);
            this->renderBackground();
            this->renderSprites();
            this->renderer->drawScreen();
        }
        else if (this->cycleCounter == VBLANK_STARTS)
            this->setVblankStatusFLag();

        this->cycleCounter = (this->cycleCounter +1) % MAX_CYCLE;
    }
    else
        --this->warmupCycles;

}

void Ppu::setVblankStatusFLag()
{
    this->statusFlags |= VBLANK_FLAG;

    if (this->isVblankEnabled())
        this->notifyListeners({"nmiinterrupt"});
}

void Ppu::writeStatusToMemory()
{
    this->memory->setAt(0x2002, this->statusFlags);
    this->statusFlags = this->statusFlags & 0b01111111;

    switch (this->controlFlags & 0b00000011)
    {
        case 0: this->memoryAddress.address = NAME_0;
        case 1: this->memoryAddress.address = NAME_1;
        case 2: this->memoryAddress.address = NAME_2;
        case 3: this->memoryAddress.address = NAME_3;
    }
}

void Ppu::setOutputMaskFlags(uint8_t maskFlags)
{
    this->outputMaskFlags = maskFlags;
}

void Ppu::setOAMAddress(uint8_t address)
{
    this->oamAddress = address;
}

void Ppu::writeOAM(uint8_t data)
{
    this->vram->writeOAM(this->oamAddress, data);

    ++this->oamAddress;
}


void Ppu::triggerDMA(uint16_t memoryPrefix)
{
    for (auto i = 0; i < OAM_SIZE; ++i)
    {
        this->vram->writeOAM(this->oamAddress, this->memory->getFrom(memoryPrefix + i));
        ++this->oamAddress;
    }
}


void Ppu::setMemoryAddress(uint8_t addressPart)
{
    this->memoryAddress.address = (this->memoryAddress.nextPart == LOW_BYTE)
        ? (this->memoryAddress.address & 0xFF00) + addressPart
        : (this->memoryAddress.address & 0x00FF) + ((addressPart) << 8);
    //: (this->memoryAddress.address & 0x00FF) + ((addressPart % 0x40) << 8);

    this->memoryAddress.nextPart = (this->memoryAddress.nextPart == LOW_BYTE) ? HIGH_BYTE : LOW_BYTE;
}


void Ppu::writeMemory(uint8_t data)
{
    this->vram->writeMemory(this->memoryAddress.address, data);

    this->memoryAddress.address += this->getVramAddressIncrement();
}

void Ppu::readMemory()
{
    uint8_t workingAddress = this->memoryAddress.address % VRAM_SIZE;

    if (workingAddress < PALETTE_STARTS)
    {
        this->memory->setAt(0x2007, this->memoryAddress.readBuffer);
        this->memoryAddress.readBuffer = this->vram->readMemory(workingAddress);
    }
    else
    {
        this->memory->setAt(0x2007, this->vram->readMemory(workingAddress));

        uint8_t newAddress = VRAM_SIZE + (workingAddress - PALETTE_STARTS) % VRAM_SIZE;
        this->memoryAddress.readBuffer = vram->readMemory(newAddress);
    }

    this->memoryAddress.address += this->getVramAddressIncrement();
}

void Ppu::updateControlFlags(uint8_t newValue)
{
    this->controlFlags = newValue;
}

void Ppu::readOAM()
{
    auto result = this->vram->readOAM(this->oamAddress);
    this->memory->setAt(0x2004, result);
}

bool Ppu::isVblankEnabled()
{
    return (this->controlFlags & VBLANK_FLAG) > 0;
}

void Ppu::unsetVblankStatusFlag()
{
    this->statusFlags &= ~(VBLANK_FLAG);
}

void Ppu::renderSprites()
{
    const uint16_t patternAddressBase = this->getSpritePatternAddress();
    for (uint16_t k = 0; k < OAM_SIZE; k += 4)
    {
        Cords position = { .horizontal = this->vram->readOAM(this->oamAddress + k + 3), .vertical = this->vram->readOAM(this->oamAddress + k) };
        const uint8_t spriteAttribute = this->vram->readOAM(this->oamAddress + k+2);
        const uint16_t colorBase = PALETTE_STARTS + (1 << 4) + ((spriteAttribute & SPRITE_ATTRIBUTE_COLOR) << 2);
        const uint16_t patternIndex = (this->vram->readOAM(this->oamAddress + k+1)) << 4;

        for (uint8_t i = 0; i <= 0x7; ++i)
        {
            const uint8_t lower = this->vram->readMemory(patternAddressBase + patternIndex + i);
            const uint8_t upper = this->vram->readMemory(patternAddressBase + patternIndex + i + 0x8);

            for (uint j = 0; j < 8; ++j)
            {
                const uint8_t colorIndex = (((upper & (0b1 << j)) >> j) << 1) + (lower & (0b1 << j) >> j);
                const uint8_t color = (colorIndex != 0) ? this->vram->readMemory(colorBase + colorIndex) : this->vram->readMemory(UNIVERSAL_BG_COLOR);

                Color pixelColor;
                if (colorIndex == 0)
                    pixelColor = { .red = 0, .green = 0, .blue = 0, .alpha = 0 };
                else if (colorIndex == 1)
                    pixelColor = { .red = 9, .green = 9, .blue = 255, .alpha = 0 };
                else if (colorIndex == 2)
                    pixelColor = { .red = 0, .green = 255, .blue = 0, .alpha = 0 };
                else if (colorIndex == 3)
                    pixelColor = { .red = 255, .green = 0, .blue = 0, .alpha = 0 };

                if (colorIndex != 0)
                {
                    Cords pixelPosition = {.horizontal = 0, .vertical = 0};
                    pixelPosition.vertical = position.vertical + i;
                    pixelPosition.horizontal = position.horizontal + (7 - j);

                    this->renderer->colorPixel(pixelPosition, pixelColor);
                }

            }
        }
    }
}

void Ppu::renderBackground()
{
    uint16_t baseNametable = this->getBaseNametableAddress();
    uint16_t basePattern = this->getBackgroundPatternAddress();
    for (auto n = 0; n < NAME_SIZE; ++n)
    {
        //this->memoryAddress.address = baseNametable + n;
        Cords position = {.horizontal = 0, .vertical = 0};
        position.horizontal = n % 32 * 8;
        position.vertical = n / 32 * 8;

        uint8_t nametableEntry = this->vram->readMemory(baseNametable + n);
        uint16_t patternStart = basePattern + (nametableEntry << 4) + 0;

        uint16_t attributeEntryAddress = (n/32/4*8)+(n%32/4) + BASE_NAMETABLE + NAME_SIZE;
        uint8_t attributeEntry = this->vram->readMemory(attributeEntryAddress);

        uint8_t verticalPos = ((((n /32) /4) %4) < 2) ? 0 : 4;
        uint8_t horizontalPos = ((((n %32) /4) %4) < 2) ? 0 : 2;
        uint8_t shiftValue = verticalPos + horizontalPos;

        uint8_t palettIndex = ((attributeEntry & (0b11  << shiftValue)) >> shiftValue);

        uint16_t colorBase = PALETTE_STARTS + (0 << 4) + (palettIndex << 2);

        for (uint8_t i = 0; i <= 0x7; ++i)
        {
            const uint8_t lower = this->vram->readMemory(patternStart + i);
            const uint8_t upper = this->vram->readMemory(patternStart + i + 0x8);

            for (uint j = 0; j < 8; ++j)
            {
                const uint8_t colorIndex = (((upper & (0b1 << j)) >> j) << 1) + (lower & (0b1 << j) >> j);

                if (colorIndex != 0)
                {
                    Color pixelColor = colors[this->vram->readMemory(colorBase + colorIndex)];

                    Cords pixelPosition = {.horizontal = 0, .vertical = 0};
                    pixelPosition.vertical = position.vertical + i;
                    pixelPosition.horizontal = position.horizontal + (7 - j);

                    this->renderer->colorPixel(pixelPosition, pixelColor);
                }

            }
        }
    }
}

uint16_t Ppu::getBaseNametableAddress()
{
    uint16_t baseNumber = this->controlFlags & BASE_NAMETABLE;
    return ((NAME_SIZE * baseNumber) + 0x2000);
}

uint16_t Ppu::getBackgroundPatternAddress()
{
    return this->getPatternData(PATTERN_BACKGROUND);
}

uint16_t Ppu::getSpritePatternAddress()
{
    return this->getPatternData(PATTERN_SPRITE);
}

uint16_t Ppu::getPatternData(uint8_t mask)
{
    auto patternAddressFlag = this->controlFlags & mask;

    return (patternAddressFlag == 0) ? 0x0000 : 0x1000 ;
}

