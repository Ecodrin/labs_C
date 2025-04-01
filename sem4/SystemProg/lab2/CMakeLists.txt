cmake_minimum_required(VERSION 3.20)
project(MyProject)
set(CMAKE_CXX_STANDARD 20)


set(COMMON_FLAGS
        -Wall
        -Wextra
        -Wpedantic
        -Werror
)


foreach (I RANGE 1 4) 
    set(TASK_FOLDER "ex${I}")
    if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${TASK_FOLDER})
        add_subdirectory(${TASK_FOLDER})
    else ()
        message("${TASK_FOLDER} doesn't exist")
    endif ()
endforeach ()