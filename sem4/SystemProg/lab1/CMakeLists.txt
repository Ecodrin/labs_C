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

add_executable(ex3 ex3/main.c
        ex3/utility.c
        libs/CustomErrors/errors.c
        ex3/utility.h
        libs/mstring/mstring.c)

add_executable(ex4_server ex4/server/server.c
        ex4/server/utility.c
        ex4/server/utility.h
        ex4/tokens.h
        libs/CustomErrors/errors.c
        libs/mstring/mstring.c)

add_executable(ex4_client
        ex4/client/client.c
        ex4/tokens.h
        ex4/client/utility.c
        libs/CustomErrors/errors.c
        libs/mstring/mstring.c
        libs/vector/charvector.c)


target_link_libraries(ex3 -lpthread)
target_link_libraries(ex4_client -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(ex4_server -Wall -Wextra -Wpedantic -Werror)
