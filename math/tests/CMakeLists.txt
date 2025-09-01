include_directories(../)
add_executable(SIMUCE_MATH_TEST_EXE test.c)
target_link_libraries(SIMUCE_MATH_TEST_EXE simuce-math)
add_test(SIMUCE_MATH_TEST SIMUCE_MATH_TEST_EXE)