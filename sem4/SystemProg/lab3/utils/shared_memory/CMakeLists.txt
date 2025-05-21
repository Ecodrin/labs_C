add_library(server_shared_memory
        include/server_shared_memory.hpp
        src/server_shared_memory.cpp
)

add_library(client_shared_memory
        include/client_shared_memory.hpp
        src/client_shared_memory.cpp
)

target_include_directories(server_shared_memory PUBLIC include)
target_include_directories(client_shared_memory PUBLIC include)
