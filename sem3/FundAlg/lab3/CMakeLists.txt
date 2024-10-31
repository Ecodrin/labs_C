cmake_minimum_required(VERSION 3.28)
project(lab3 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1 ex1/main.c
        ex1/ex1.c
        ex1/ex1.h)

target_link_libraries(ex1 errors -L../lib)


add_executable(ex2 ex2/main.c
        ex2/ex2.c
        ex2/ex2.h)

add_executable(ex3 ex3/main.c
        ex3/ex3.c
        ex3/ex3.h)



add_executable(ex4
        ex4/main.c
        ex4/test.h
        ex4/mail.c
        ex4/mail.h)

add_executable(ex5 ex5/main.c
        ex5/ex5.c
        ex5/ex5.h
        ../lib/vector/charvector.c
        ../lib/vector/intvector.c
        ../lib/mstring/mstring.c)


add_executable(ex6
        ex6/main.c
        lib/vector/charvector.c
        lib/mstring/mstring.c
        ex6/ex6.c
        ex6/ex6.h
)

add_executable(ex10 ex10/ex10.c
        ex10/ex10.h
        ex10/main.c
        ../lib/vector/charvector.c
        ../lib/mstring/mstring.c)


target_link_libraries(ex3 m mstring errors -L../lib)
target_link_libraries(ex2 m errors -L../lib)
target_link_libraries(ex5 m errors -L../lib)
target_link_libraries(ex4 -Wall -Wextra -Werror -g -lm -lerrors -lmstring -lvector -L../lib/ -std=c99 )
target_link_libraries(ex10 m errors -L../lib)
