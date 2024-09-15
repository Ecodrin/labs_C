cmake_minimum_required(VERSION 3.28)
project(lab1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(lab1
        intvector.c
        intvector.h
        main.c)
