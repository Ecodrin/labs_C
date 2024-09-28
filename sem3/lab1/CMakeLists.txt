cmake_minimum_required(VERSION 3.28)
project(lab1 C)

set(CMAKE_C_STANDARD 11)

include_directories(ex1)

add_executable(t1
        ex1/main.c
        ex1/ex1.c
        ex1/ex1.h
        vector/intvector.c
        vector/intvector.h
        vector/charvector.c
        vector/charvector.h)

add_executable(t2
        ex2/main.c
        ex2/ex2.c
        ex2/ex2.h)

add_executable(t4
        ex4/main.c
        ex4/ex4.c
        ex4/ex4.h)

add_executable(t5
        ex5/main.c
        ex5/ex5.c
        ex5/ex5.h)

add_executable(t7
        ex7/main.c
        ex7/ex7.c
        ex7/ex7.h)

add_executable(t8
        ex8/main.c
        ex8/ex8.c
        ex8/ex8.h)


add_executable(t9
        ex9/main.c
        ex9/ex9.c
        ex9/ex9.h
        vector/intvector.c
        vector/intvector.h)

add_executable(t10
        ex10/main.c
        vector/charvector.c
        vector/charvector.h
        ex10/ex10.c
        ex10/ex10.h)

target_link_libraries(t1 m)
target_link_libraries(t2 m)

target_link_libraries(t4 m)
target_link_libraries(t5 m)

target_link_libraries(t7 m)
target_link_libraries(t9 m)