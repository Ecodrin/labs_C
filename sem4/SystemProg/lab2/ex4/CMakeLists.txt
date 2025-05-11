cmake_minimum_required(VERSION 3.28)
project(ex4)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex4 main.cpp
        include/logger.hpp
        src/logger.cpp
        include/unility.hpp
        src/unitily.cpp)
