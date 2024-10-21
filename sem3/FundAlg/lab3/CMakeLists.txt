cmake_minimum_required(VERSION 3.28)
project(lab3 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1 ex1/main.c
        ex1/ex1.c
        ex1/ex1.h
        ex1/test.c
        ex1/test.h)

target_link_libraries(ex1 m mstring vector -L../lib check subunit rt pthread)


add_executable(ex2 ex2/main.c
        ex2/ex2.c
        ex2/ex2.h
        ex2/test.c
        ex2/test.h)

add_executable(ex3 ex3/main.c
        ex3/ex3.c
        ex3/ex3.h)

target_link_libraries(ex3 m mstring errors -L../lib)


add_executable(ex4
        ex4/test.c
        ex4/test.h)


target_link_libraries(ex4 -Wall -Wextra -Werror -g -lm -lcheck -lsubunit -lrt -lpthread -lerrors -lmstring -lvector -L../lib/ -std=c99  `pkg-config --cflags --libs check`)