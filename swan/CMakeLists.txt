cmake_minimum_required(VERSION 3.10.0)
project(simuce-swan VERSION 0.1.0 LANGUAGES C)

enable_testing()

add_subdirectory(tests)
add_subdirectory(../base ../base/build)

include_directories(../base)

add_library(simuce-swan
    swan_header.h
    globals.h globals.c
    treegen.h treegen.c
    token.h token.c
    swan.h swan.c)

target_link_libraries(simuce-swan PUBLIC simuce-base)