cmake_minimum_required(VERSION 3.28)
project(ex2)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex2 tests/main.cpp

        include/safe_queue.hpp
        include/logs_generator.hpp
        src/logs_generator.cpp
        tests/main.cpp
        include/logs_analyzer.hpp
        src/logs_analyzer.cpp
        src/logger.cpp
        include/logger.hpp
        src/safe_queue.cpp)
