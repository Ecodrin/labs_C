cmake_minimum_required(VERSION 3.22.1)
project(ex2)


set(CMAKE_CXX_STANDARD 17)


set(CMAKE_C_FLAGS
        -Wall
        -Werror
        -Wextra
        -fsanitize=address
)

add_executable(ex2_client
        client/include/client.hpp
        client/include/logger.hpp
        client/src/client.cpp
        client/src/logger.cpp
        client/main.cpp
        client/src/shared_memory.cpp
        client/include/shared_memory.hpp
)

add_executable(ex2_server
        server/include/logger.hpp
        server/include/server.hpp
        server/src/logger.cpp
        server/src/server.cpp
        server/main.cpp
        server/src/shared_memory.cpp
)

