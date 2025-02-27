cmake_minimum_required(VERSION 3.22.1)
project(lab1 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1 ex1/main.c
        ex1/utility.c
        ex1/utility.h
        libs/CustomErrors/errors.h
        libs/CustomErrors/errors.c
        libs/mstring/mstring.c
        libs/vector/charvector.c)

add_executable(ex2 ex2/main.c
        ex2/utility.c
        ex2/utility.h
        libs/CustomErrors/errors.c
        libs/mstring/mstring.c
        libs/vector/charvector.c)


SET(CMAKE_C_FLAGS "-fsanitize=address")