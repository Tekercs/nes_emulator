add_executable(emulator_test helpers/DummyRenderer.h helpers/DummyRenderer.cpp testVRamAccess.cpp test.cpp test_memory.cpp test_cartridge.cpp test_cpu.cpp helpers/TestCpuHelpers.cpp helpers/TestCpuHelpers.h)


target_link_libraries(emulator_test LINK_PUBLIC emulator)
target_include_directories(emulator_test PRIVATE ../libs)
