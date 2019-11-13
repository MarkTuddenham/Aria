cmake_minimum_required(VERSION 3.10)

project(DarkChessExample VERSION 0.1)

# add the executable
add_executable(DarkChessExample dark_chess.cpp)

target_link_libraries(DarkChessExample 
PRIVATE
    DarkChess
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	target_compile_definitions(DarkChessExample PRIVATE "DEBUG")
endif()

target_include_directories(DarkChessExample 
PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_BINARY_DIR}"
    "${LIBRARY_OUTPUT_PATH}"
)
