cmake_minimum_required(VERSION 3.28)
project(ex2)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex2 tests/main.cpp
        tests/main.cpp
        src/logger.cpp
        include/logger.hpp
)
