cmake_minimum_required(VERSION 3.10.0)
project(simuce-base VERSION 0.1.0 LANGUAGES C)

enable_testing()

add_subdirectory(tests)

add_library(simuce-base
    header.h
    debug.h debug.c
    fileio.h fileio.c
    memory.h memory.c
    simuce-base.h simuce-base.c)

