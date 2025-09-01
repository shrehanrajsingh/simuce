cmake_minimum_required(VERSION 3.10.0)
project(simuce-math VERSION 0.1.0 LANGUAGES C)

enable_testing()

add_subdirectory(tests)

add_library(simuce-math
    simuce-math.h simuce-math.c)

