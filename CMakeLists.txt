cmake_minimum_required(VERSION 3.14)
project(Simple-Lexer C)

set(CMAKE_C_STANDARD 99)

option(SL_SHARED_BUILD "Enable shared build" OFF)

if(SL_SHARED_BUILD)
    set(SL_STATIC SHARED)
else()
    set(SL_STATIC STATIC)
endif()

add_subdirectory(extlibs/datatypes.h)

add_subdirectory(src/)
add_subdirectory(example/)
