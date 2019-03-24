add_library(emulator SHARED Ppu/Renderer.h Ppu/Renderer.cpp Ppu/ColorPalette.h Ppu/Ppu.h Ppu/Ppu.cpp Utils/Listener.cpp Utils/Listener.h Utils/EventSource.h Utils/EventSource.cpp Ppu/VRam.h Ppu/VRam.cpp Memory/Memory.cpp Memory/Memory.h Rom/Cartridge.cpp Rom/Cartridge.h Cpu/Cpu.cpp Cpu/Cpu.h Rom/Mapper.cpp Rom/Mapper.h Rom/MapperNrom.cpp Rom/MapperNrom.h Cpu/Registers.cpp Cpu/Registers.h Utils/Converters.cpp Utils/Converters.h Utils/Controller.cpp Utils/Controller.h)

target_include_directories (emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
