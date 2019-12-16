cmake_minimum_required(VERSION 3.10)

configure_file(config.hpp.in config.hpp)

add_library(Aria 
            core/board.cpp
            core/fen.cpp
            core/log.cpp
            core/piece.cpp
            core/utils.cpp
            )
            
add_subdirectory(vendor/spdlog/)


set(TARGET_COMPILE_DEFINITIONS "")
set(TARGET_PRIVATE_LINK_LIBS "")

if (WIN32)
    list(APPEND TARGET_COMPILE_DEFINITIONS "PLATFORM_WINDOWS")
elseif(UNIX)
    list(APPEND TARGET_COMPILE_DEFINITIONS "PLATFORM_LINUX")
endif()
target_compile_definitions(Aria PRIVATE ${TARGET_COMPILE_DEFINITIONS})


if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    list(APPEND TARGET_COMPILE_DEFINITIONS "DEBUG" "PROFILING")
endif()


if(MSVC)
    target_compile_options(Aria
    PRIVATE
        "/W4"
    )
else()
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        target_compile_options(Aria
        PRIVATE
            "-O1"
            "-Wextra"
            "-Wpedantic"
            "-Wshadow"
            "-Wnon-virtual-dtor"
            "-Wnull-dereference"
            "-Wold-style-cast"
            "-Wuseless-cast"
            "-Wformat=2"
            "-fsanitize=address"
        )
        list(APPEND TARGET_PRIVATE_LINK_LIBS -fsanitize=address)
    else()
        target_compile_options(Aria
        PRIVATE
            "-O3"
        )
    endif()
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


target_link_libraries(Aria
PRIVATE
    ${TARGET_PRIVATE_LINK_LIBS}
PUBLIC
    spdlog
)
