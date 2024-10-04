cmake_minimum_required(VERSION 3.28)
project(lab2 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1
        SystemErrors/errors.c
        SystemErrors/errors.h
        ex1/ex1.c
        ex1/ex1.h
        ex1/main.c
        vector/charvector.h
        vector/charvector.c)


add_executable(ex2 ex2/main.c
        SystemErrors/errors.c
        SystemErrors/errors.h
        ex2/ex2.c
        ex2/ex2.h)


target_link_libraries(ex2 m)