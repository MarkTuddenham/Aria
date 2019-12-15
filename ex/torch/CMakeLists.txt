cmake_minimum_required(VERSION 3.10)

project(TorchExample VERSION 0.1)

# find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# add the executable
add_executable(TorchExample torch.cpp)

target_link_libraries(TorchExample 
PRIVATE
    DarkChess
    "${TORCH_LIBRARIES}"
)

if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET TorchExample
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:TorchExample>)
endif (MSVC)

set(COMPILE_OPTIONS "")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    list(APPEND COMPILE_OPTIONS "DEBUG" "PROFILING")
endif()

if (WIN32)
    list(APPEND COMPILE_OPTIONS "PLATFORM_WINDOWS")
elseif(UNIX)
    list(APPEND COMPILE_OPTIONS "PLATFORM_LINUX")
endif()

target_compile_definitions(TorchExample PRIVATE ${COMPILE_OPTIONS})

target_include_directories(TorchExample 
PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_BINARY_DIR}"
    "${LIBRARY_OUTPUT_PATH}"
)
