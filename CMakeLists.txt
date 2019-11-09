cmake_minimum_required(VERSION 3.10)

# set the project name
project(DarkChess VERSION 0.1)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

add_subdirectory(dark_chess)
add_subdirectory(ex)