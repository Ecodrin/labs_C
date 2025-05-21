add_library(server_tcp
        include/server_tcp.hpp
        src/server_tcp.cpp
)

add_library(client_tcp
        include/client_tcp.hpp
        src/client_tcp.cpp
)


target_include_directories(server_tcp PUBLIC include)
target_include_directories(client_tcp PUBLIC include)

target_link_libraries(server_tcp
        PRIVATE custom_exceptions
        PRIVATE logger
)
target_link_libraries(client_tcp
        PRIVATE custom_exceptions
        PRIVATE logger
)