cmake_minimum_required(VERSION 3.8)

# set a variable on the project's name to easily rename it if needed
set(This A429Library)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

option(BUILD_32bit "option to build library in 32bit environment" OFF)
if(BUILD_32bit)
    message("BUILD WITH 32BIT ENVIRONMENT")
    set(CMAKE_C_FLAGS -m32)
    set(CMAKE_CXX_FLAGS -m32)
    # alternative to above lines
#    add_compile_options(-m32)
else()
    message("BUILD WITH 64BIT ENVIRONMENT")
endif(BUILD_32bit)
unset(BUILD_32bit CACHE) # <---- this is important to update the cache with option value!!

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