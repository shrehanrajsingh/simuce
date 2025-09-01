include_directories(../)
add_executable(SIMUCE_BASE_TEST_EXE test.c)
target_link_libraries(SIMUCE_BASE_TEST_EXE simuce-base)
add_test(SIMUCE_BASE_TEST SIMUCE_BASE_TEST_EXE)