# A429Library
Simple C++ Library to decode ARINC 429 words


## In order to run test on Windows
add the following line in the Cmake file of googletest: googletest/CMakeLists.txt
set( gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)


## CMake options
BUILD_32bit: ON to build library for a 32bit environment. Default value is OFF.

## How to use CMake options
Just add -DOPTION_NAME=VALUE in cmake command line (e.g. -DBUILD_32bit=ON, ...)
