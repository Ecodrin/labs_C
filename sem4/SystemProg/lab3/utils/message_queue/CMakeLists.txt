add_library(server_queue_msgs
        include/server_message_queue.hpp
        src/server_message_queue.cpp
)

add_library(client_queue_msgs
        include/client_message_queue.hpp
        src/client_message_queue.cpp
)

target_include_directories(server_queue_msgs PUBLIC include)
target_include_directories(client_queue_msgs PUBLIC include)
