add_executable(ui main.cpp GameWindow.cpp GameWindow.h)

find_package(SDL2 REQUIRED)
find_package(SDL2)

target_include_directories (ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})
target_link_libraries(ui PUBLIC SDL2::SDL2)

target_link_libraries (ui LINK_PUBLIC emulator)