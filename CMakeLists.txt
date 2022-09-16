cmake_minimum_required(VERSION 3.14)
project(Simple-Lexer C)

set(CMAKE_C_STANDARD 99)

option(SL_STATIC_BUILD "Enable static build" ON)

if(SL_STATIC_BUILD)
    set(SL_STATIC STATIC)
else()
    set(SL_STATIC SHARED)
endif()

add_subdirectory(src/)
add_subdirectory(example/)
