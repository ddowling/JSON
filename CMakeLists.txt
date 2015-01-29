cmake_minimum_required(VERSION 2.8)

find_package(Boost)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(JSON
    JSON.cpp
)

enable_testing()
add_subdirectory(test)

