add_executable(server
        src/main.cpp
        include/server.hpp
        src/server.cpp
)


target_link_directories(server PRIVATE include)

target_link_libraries(server
        PRIVATE server_tcp
        PRIVATE logger
        PRIVATE client_queue_msgs
        PRIVATE client_shared_memory
        PRIVATE custom_exceptions
)