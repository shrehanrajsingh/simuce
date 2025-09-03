include_directories(../)
add_executable(SCE_SWAN_TEST_EXE test.c)
target_link_libraries(SCE_SWAN_TEST_EXE swan)
add_test(SCE_SWAN_TEST SCE_SWAN_TEST_EXE)