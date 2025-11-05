cmake_minimum_required(VERSION 3.10)
project(MatrixMultiplier)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

set(SOURCES
    src/main.cpp
    src/Matrix.cpp
    src/ThreadMultiplier.cpp
    src/PthreadMultiplier.cpp
)

add_executable(matrix_multiplier ${SOURCES})

target_link_libraries(matrix_multiplier ${CMAKE_THREAD_LIBS_INIT})

target_compile_options(matrix_multiplier PRIVATE -Wall -Wextra -O2)
