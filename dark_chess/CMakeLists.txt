cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-O3 -pthread -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor")

configure_file(config.hpp.in config.hpp)

add_library(DarkChess 
                board.cpp
                piece.cpp
                utils.cpp
                )

target_include_directories(DarkChess PUBLIC "${PROJECT_BINARY_DIR}/" "${PROJECT_SOURCE_DIR}/")