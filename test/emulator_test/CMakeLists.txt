add_executable(emulator_test test.cpp test_memory.cpp test_cartridge.cpp test_cpu.cpp helpers/TestCpuHelpers.cpp helpers/TestCpuHelpers.h)


target_link_libraries(emulator_test LINK_PUBLIC emulator)
target_include_directories(emulator_test PRIVATE ../libs)
