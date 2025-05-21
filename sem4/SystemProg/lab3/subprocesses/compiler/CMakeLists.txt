add_executable(compiler
        include/compiler.hpp
        src/compiler.cpp
        src/main.cpp
)

target_include_directories(compiler PRIVATE include)
target_link_libraries(compiler PRIVATE logger server_shared_memory)