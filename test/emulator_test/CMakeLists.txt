add_executable(emulator_test test.cpp)


target_link_libraries(emulator_test LINK_PUBLIC emulator)
target_include_directories(emulator_test PRIVATE ../libs)
