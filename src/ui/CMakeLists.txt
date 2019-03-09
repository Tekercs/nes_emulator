add_executable(ui main.cpp)

find_package(SDL2 REQUIRED)
find_package(SDL2)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(ui PUBLIC SDL2::SDL2)

target_link_libraries (ui LINK_PUBLIC emulator)