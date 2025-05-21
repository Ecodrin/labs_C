cmake_minimum_required(VERSION 3.22)
project(SysProg/Lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_compile_options(
        -std=c++20
        -Wall
        -Wextra
        -Wpedantic
        -Werror
)

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(utils)
add_subdirectory(subprocesses)