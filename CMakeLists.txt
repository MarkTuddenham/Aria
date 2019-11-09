cmake_minimum_required(VERSION 3.10)

project(DarkChess VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/lib)


# if(MSVC)
#     add_compile_options(/W3 /WX)
# else()
#     add_compile_options(-W -Wall -Werror)
# endif()

add_subdirectory(DarkChess)
add_subdirectory(ex)