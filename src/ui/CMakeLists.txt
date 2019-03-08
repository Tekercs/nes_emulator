add_executable(ui main.cpp)

set (CMAKE_CXX_FLAGS "-lSDL2")

target_link_libraries (ui LINK_PUBLIC emulator)
