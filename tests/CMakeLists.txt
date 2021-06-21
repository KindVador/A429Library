cmake_minimum_required(VERSION 3.8)

# set a variable on the project's name to easily rename it if needed
set(This A429LibraryTests)

set(Sources
    a429wordtests.cpp
    a429bnrwordtests.cpp
    a429bcdwordtests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    A429Library
)

add_test(
    NAME ${This}
    COMMAND ${This}
)