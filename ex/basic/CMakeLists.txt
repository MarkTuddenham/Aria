cmake_minimum_required(VERSION 3.10)

project(DarkChessExample VERSION 0.1)

# add the executable
add_executable(DarkChessExample dark_chess.cpp)

target_link_libraries(DarkChessExample 
PRIVATE
    DarkChess
)

set(COMPILE_OPTIONS "")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    list(APPEND COMPILE_OPTIONS "DEBUG" "PROFILING")
endif()

if (WIN32)
    list(APPEND COMPILE_OPTIONS "PLATFORM_WINDOWS")
elseif(UNIX)
    list(APPEND COMPILE_OPTIONS "PLATFORM_LINUX")
endif()

target_compile_definitions(DarkChessExample PRIVATE ${COMPILE_OPTIONS})

target_include_directories(DarkChessExample 
PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_BINARY_DIR}"
    "${LIBRARY_OUTPUT_PATH}"
)
