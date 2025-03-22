cmake_minimum_required(VERSION 3.10.0)
project(MyGame VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(PROJECT_ROOT "${CMAKE_SOURCE_DIR}")
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/config)
configure_file(${CMAKE_SOURCE_DIR}/config/config.h.in ${CMAKE_BINARY_DIR}/config/config.h @ONLY)

add_compile_definitions(
    DEBUG_MODE=1
)

add_subdirectory(thirdparty/SDL EXCLUDE_FROM_ALL)
add_subdirectory(src)
