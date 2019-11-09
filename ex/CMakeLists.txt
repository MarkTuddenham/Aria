cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(DarkChessExample dark_chess.cpp)

target_link_libraries(DarkChessExample PUBLIC DarkChess)

target_include_directories(DarkChessExample PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            )