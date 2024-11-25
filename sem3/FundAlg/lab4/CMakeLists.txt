cmake_minimum_required(VERSION 3.22)
project(lab4 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1 ex1/main.c
        ex1/ex1.c
        ex1/ex1.h
        lib/SystemErrors/errors.c
        lib/vector/charvector.c
        lib/mstring/mstring.c
)
add_executable(ex2 ex2/ex2.c ex2/ex2.h
        ex2/main.c
        lib/SystemErrors/errors.c
        lib/vector/charvector.c
        lib/vector/intvector.c
        lib/mstring/mstring.c)


add_executable(ex7 ex7/main.c
        ex7/ex7.c
        ex7/ex7.h
        lib2/SystemErrors2/errors.c
        lib2/vector/charvector.c
        lib2/mstring/mstring.c
)
add_executable(ex9
        ex9/main.c
        lib2/SystemErrors2/errors.c
        lib2/vector/charvector.c
        lib2/mstring/mstring.c
        lib2/universal_vector/vector.c
        lib2/universal_vector/vector.h
        ex9/application/application.h
        ex9/application/application.c
        ex9/heaps/heaps.c
        ex9/heaps/heaps.h
        ex9/heaps/binary-heap/binary-heap.c
        ex9/heaps/binary-heap/binary-heap.h
        ex9/heaps/binomial-heap/binomial-heap.c
        ex9/heaps/binomial-heap/binomial-heap.h)
