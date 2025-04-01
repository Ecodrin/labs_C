add_library(liblogger
        include/logger.hpp
        src/logger.cpp)

add_executable(ex1 tests/test_logger.cpp)

target_link_libraries(ex1 PUBLIC liblogger)