cmake_minimum_required(VERSION 3.22)
project(lab2 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab2 main.c
        utility/utility.h
        utility/utility.c
        SystemErrors/errors.c
        SystemErrors/errors.h
        utility/functions.c
        utility/functions.h
)

set(CMAKE_C_FLAGS -fsanitize=thread)

target_link_libraries(lab2 -lpthread)

