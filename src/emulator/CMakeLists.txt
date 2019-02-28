add_library(emulator SHARED Memory/Memory.cpp Memory/Memory.h Rom/Cartridge.cpp Rom/Cartridge.h Cpu/Cpu.cpp Cpu/Cpu.h Rom/Mapper.cpp Rom/Mapper.h Rom/MapperNrom.cpp Rom/MapperNrom.h Cpu/Registers.cpp Cpu/Registers.h)

target_include_directories (emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
