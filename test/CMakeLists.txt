cmake_minimum_required(VERSION 3.10)

project(Tests VERSION 0.1)

# add the executable
add_executable(Tests 
    src/test.cpp
    src/board.cpp
    src/checks.cpp
    src/fen.cpp
)

target_link_libraries(Tests 
PRIVATE
    DarkChess
)

set(COMPILE_OPTIONS "")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    list(APPEND COMPILE_OPTIONS "DEBUG")
endif()

if (WIN32)
    list(APPEND COMPILE_OPTIONS "PLATFORM_WINDOWS")
elseif(UNIX)
    list(APPEND COMPILE_OPTIONS "PLATFORM_LINUX")
endif()

target_compile_definitions(Tests PRIVATE ${COMPILE_OPTIONS})

target_include_directories(Tests 
PRIVATE
    "include/"
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_BINARY_DIR}"
    "${LIBRARY_OUTPUT_PATH}"
)
