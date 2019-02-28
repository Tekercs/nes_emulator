add_library(emulator SHARED Memory/memory.cpp Memory/memory.h Rom/cartridge.cpp Rom/cartridge.h Cpu/cpu.cpp Cpu/cpu.h Rom/mapper.cpp Rom/mapper.h Rom/mapper_nrom.cpp Rom/mapper_nrom.h)

target_include_directories (emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
