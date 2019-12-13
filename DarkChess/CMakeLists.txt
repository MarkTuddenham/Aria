cmake_minimum_required(VERSION 3.10)

configure_file(config.hpp.in config.hpp)

add_library(DarkChess 
            core/board.cpp
            core/piece.cpp
            core/utils.cpp
            core/log.cpp
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

target_compile_definitions(DarkChess PRIVATE ${COMPILE_OPTIONS})

if(MSVC)
    target_compile_options(DarkChess
    PRIVATE
        "/W4"
    )
else()
    target_compile_options(DarkChess
    PRIVATE
        "-O1" 
        # "-pthread"
        "-Wextra"
        "-Wpedantic"
        "-Wshadow"
        "-Wnon-virtual-dtor"
        "-Wnull-dereference"
        "-Wold-style-cast"
        "-Wuseless-cast"
        "-Wformat=2"
    )
endif()

target_include_directories(DarkChess
PRIVATE
    "${PROJECT_SOURCE_DIR}/DarkChess/vendor/"
PUBLIC
    "${PROJECT_SOURCE_DIR}/" 
    "${PROJECT_BINARY_DIR}/"
INTERFACE
    "${PROJECT_SOURCE_DIR}/DarkChess"
)

add_subdirectory(vendor/spdlog/)

target_link_libraries(DarkChess
PUBLIC
    spdlog
)
