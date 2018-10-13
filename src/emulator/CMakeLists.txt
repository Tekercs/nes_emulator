add_library(emulator SHARED library.cpp library.h)

target_include_directories (emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
