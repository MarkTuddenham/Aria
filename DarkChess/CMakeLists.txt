cmake_minimum_required(VERSION 3.10)

configure_file(config.hpp.in config.hpp)

add_library(DarkChess 
            core/board.cpp
            core/piece.cpp
            core/utils.cpp
            core/log.cpp
            )

if(MSVC)

target_compile_options(DarkChess
PRIVATE
	"/W3"
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