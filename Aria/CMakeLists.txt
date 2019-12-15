cmake_minimum_required(VERSION 3.10)

configure_file(config.hpp.in config.hpp)

add_library(Aria 
            core/board.cpp
            core/fen.cpp
            core/log.cpp
            core/piece.cpp
            core/utils.cpp
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

target_compile_definitions(Aria PRIVATE ${COMPILE_OPTIONS})

if(MSVC)
    target_compile_options(Aria
    PRIVATE
        "/W4"
    )
else()
    target_compile_options(Aria
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

target_include_directories(Aria
PRIVATE
    "${PROJECT_SOURCE_DIR}/Aria/vendor/"
PUBLIC
    "${PROJECT_SOURCE_DIR}/" 
    "${PROJECT_BINARY_DIR}/"
INTERFACE
    "${PROJECT_SOURCE_DIR}/Aria"
)

add_subdirectory(vendor/spdlog/)

target_link_libraries(Aria
PUBLIC
    spdlog
)
