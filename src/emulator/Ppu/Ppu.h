#pragma once

#include <memory>
#include <initializer_list>
#include <string>
#include <functional>

#include <Ppu/VRam.h>
#include <Memory/Memory.h>
#include <Utils/Listener.h>
#include <Utils/EventSource.h>
#include <Ppu/ColorPalette.h>
#include <Ppu/Renderer.h>

#define DEFAULT_PPUCNTRL                 0b00000000
#define DEFAULT_MASKFLAGS                0b00000000
#define DEFAULT_STATUS                   0b10100000

#define VBLANK_FLAG                      0b10000000

#define RENDER_FINISH                    81840
#define VBLANK_STARTS                    82181
#define SCANLINE_CYCLES                  341
#define WARMUP_CYCLES                    88974
#define MAX_CYCLE                        89001
#define PATTERN_BACKGROUND               0b00010000
#define PATTERN_SPRITE                   0b00001000
#define SPRITE_ATTRIBUTE_COLOR           0b00000011
#define SPRITE_ATTRIBUTE_VERTICAL_FLIP   0b10000000
#define SPRITE_ATTRIBUTE_HORIZONTAL_FLIP 0b01000000

#define BASE_NAMETABLE                   0b00000011

#define INCREMENT_BIT                    0b00000100

namespace Emulator::Ppu
{
    class Ppu : public Emulator::Utils::Listener, public Emulator::Utils::EventSource
    {
    private: 
        std::shared_ptr<VRam> vram;
        std::shared_ptr<Emulator::Memory::Memory> memory;
        uint8_t oamAddress;
        struct MemoryAccessor memoryAddress;
        uint8_t controlFlags;
        uint8_t outputMaskFlags;
        uint8_t statusFlags;
        uint32_t cycleCounter;
        uint32_t warmupCycles;
        std::shared_ptr<Renderer> renderer;

        void vramAddressIncrement();

        void setVblankStatusFLag();
        void unsetVblankStatusFlag();
        bool isVblankEnabled();

        void renderSprites();
        void renderBackground();
        uint16_t getBackgroundPatternAddress();
        uint16_t getSpritePatternAddress();
        uint16_t getPatternData(uint8_t mask);
        uint16_t getBaseNametableAddress();


        void setOAMAddress(uint8_t address);
        void writeStatusToMemory();
        void readOAM();
        void writeOAM(uint8_t data);
        void triggerDMA(uint16_t memoryPrefix);
        void readMemory();
        void writeMemory(uint8_t data);
        void setMemoryAddress(uint8_t addressPart);
        void updateControlFlags(uint8_t newValue);
        void setOutputMaskFlags(uint8_t maskFlags);

    public:
        Ppu(std::shared_ptr<VRam> vram, std::shared_ptr<Emulator::Memory::Memory> memory, std::shared_ptr<Renderer> renderer);

        void notify(std::initializer_list<std::string> parameters) override;

        void operator++();
    };
}