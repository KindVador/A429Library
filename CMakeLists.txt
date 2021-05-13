cmake_minimum_required(VERSION 3.8)

# set a variable on the project's name to easily rename it if needed
set(This A429Library)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    a429word.hpp
)

set(Sources
    a429word.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(tests)