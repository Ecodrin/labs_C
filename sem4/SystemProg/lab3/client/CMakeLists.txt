add_executable(client
        src/main.cpp
        include/client.hpp
        src/client.cpp
)


target_include_directories(client PRIVATE include)


target_link_libraries(client
        PRIVATE client_tcp
        PRIVATE logger
        PRIVATE custom_exceptions
)