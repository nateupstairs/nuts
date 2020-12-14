cmake_minimum_required(VERSION 3.6)
project(Test)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)

add_executable(Test
    src/test.c
)
