add_executable(sticks_game
        include/sticks_game.hpp
        src/sticks_game.cpp
        src/main.cpp
)

target_include_directories(sticks_game PRIVATE include)
target_link_libraries(sticks_game PRIVATE server_queue_msgs logger)
