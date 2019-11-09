cmake_minimum_required(VERSION 3.10)

configure_file(config.hpp.in config.hpp)

add_library(DarkChess 
            board.cpp
            piece.cpp
            utils.cpp
            log.cpp
            )

target_compile_options(DarkChess
PRIVATE
    "-O3" 
    "-pthread"
    "-Wextra"
    "-Wpedantic"
    "-Wshadow"
    "-Wnon-virtual-dtor"
)

target_include_directories(DarkChess 
PRIVATE 
"${PROJECT_SOURCE_DIR}/DarkChess/vendor/"
PUBLIC
"${PROJECT_SOURCE_DIR}/" 
"${PROJECT_BINARY_DIR}/"
INTERFACE
"${PROJECT_SOURCE_DIR}/DarkChess"
)

add_subdirectory(vendor/spdlog)

target_link_libraries(DarkChess
PUBLIC
    spdlog::spdlog
)