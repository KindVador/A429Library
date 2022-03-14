cmake_minimum_required(VERSION 3.8)

# set a variable on the project's name to easily rename it if needed
set(This A429Library)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(3rdparty/googletest)

set(Headers
        src/a429word.hpp
        src/a429bnrword.hpp
        src/a429bcdword.hpp
)

set(Sources
        src/a429word.cpp
        src/a429bnrword.cpp
        src/a429bcdword.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(tests)