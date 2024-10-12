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


add_executable(ex3 ex3/ex3.c
        ex3/ex3.h
        SystemErrors/errors.c
        SystemErrors/errors.h
        ex3/main.c
        vector/intvector.c
        vector/stringvector.c)

add_executable(ex4 ex4/main.c
        SystemErrors/errors.c
        SystemErrors/errors.h
        ex4/ex4.c
        ex4/ex4.h
        vector/charvector.c
        vector/charvector.h
        vector/stringvector.c
        vector/stringvector.h)

add_executable(ex5 ex5/main.c
        ex5/overloads.c
        ex5/overloads.h
        vector/stringvector.c
        vector/charvector.c
        vector/charvector.h)

add_executable(ex8 ex8/main.c
        ex8/ex8.c
        SystemErrors/errors.c
        SystemErrors/errors.h
        ex8/ex8.h
        vector/stringvector.c
        vector/charvector.c
        vector/charvector.h)

target_link_libraries(ex2 m)
target_link_libraries(ex3 m)

