cmake_minimum_required(VERSION 3.10)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


add_subdirectory(basic)

find_package(Torch)
if(Torch_FOUND)
    add_subdirectory(torch)
endif()