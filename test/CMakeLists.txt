cmake_minimum_required(VERSION 3.10)

project(Tests VERSION 0.1)

# add the executable
add_executable(Tests 
    src/test.cpp
    src/checks.cpp
    src/board.cpp
)

target_link_libraries(Tests 
PRIVATE
    DarkChess
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	target_compile_definitions(Tests PRIVATE "DEBUG")
endif()

target_include_directories(Tests 
PRIVATE
    "include/"
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_BINARY_DIR}"
    "${LIBRARY_OUTPUT_PATH}"
)
