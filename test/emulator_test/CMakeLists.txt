add_executable(emulator_test test.cpp test_memory.cpp test_cartridge.cpp helpers/test_cartridge_helpers.cpp helpers/test_cartridge_helpers.h)


target_link_libraries(emulator_test LINK_PUBLIC emulator)
target_include_directories(emulator_test PRIVATE ../libs)
