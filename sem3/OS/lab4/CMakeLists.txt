cmake_minimum_required(VERSION 3.28)
project(lab4 C)

set(CMAKE_C_STANDARD 17)

add_executable(lab4 main.c)
add_executable(free-blocks-allocator free-blocks-allocators/free-block-allocator.h
        free-blocks-allocators/main.c
        free-blocks-allocators/free-block-allocator.c)
