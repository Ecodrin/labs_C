add_library(custom_exceptions
        include/custom_exceptions.hpp
        src/custom_exceptions.cpp
)

target_include_directories(custom_exceptions PUBLIC include)