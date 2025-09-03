cmake_minimum_required(VERSION 3.10.0)
project(swan VERSION 0.1.0 LANGUAGES C)

enable_testing()

add_subdirectory(tests)

add_library(swan
    swan.h swan.c)

