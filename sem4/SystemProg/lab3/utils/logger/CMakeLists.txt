add_library(logger
        include/logger.hpp
        src/logger.cpp
)


target_include_directories(logger PUBLIC include)