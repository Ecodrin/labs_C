cmake_minimum_required(VERSION 3.28)
project(lab2 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1
        SystemErrors/errors.c
        SystemErrors/errors.h
        ex1/ex1.c
        ex1/ex1.h
        ex1/main.c)


