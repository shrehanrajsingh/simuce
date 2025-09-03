cmake_minimum_required(VERSION 3.10.0)
project(simuce-math VERSION 0.1.0 LANGUAGES C)

enable_testing()

add_subdirectory(tests)
add_subdirectory(../base ../base/build)

include_directories(../base)

add_library(simuce-math
    math_header.h
    number_system.h number_system.c
    simuce-math.h simuce-math.c)

target_link_libraries(simuce-math PUBLIC simuce-base)