cmake_minimum_required(VERSION 3.10)

project(AriaExample VERSION 0.1)

# add the executable
add_executable(AriaExample aria.cpp)

target_link_libraries(AriaExample 
PRIVATE
    Aria
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

target_compile_definitions(AriaExample PRIVATE ${COMPILE_OPTIONS})

target_include_directories(AriaExample 
PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_BINARY_DIR}"
    "${LIBRARY_OUTPUT_PATH}"
)
