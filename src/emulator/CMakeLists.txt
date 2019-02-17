add_library(emulator SHARED memory.cpp memory.h cartridge.cpp cartridge.h cpu.cpp cpu.h)

target_include_directories (emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
