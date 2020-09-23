cmake_minimum_required(VERSION 3.11)
include(FetchContent)

project(Zinet)

# Print CMake source dir
message(STATUS "*** CMakeList source dir : " ${CMAKE_SOURCE_DIR} " ***")

# Print C++ compiler path
message(STATUS "*** C++ compiler path: " ${CMAKE_CXX_COMPILER} " ***")

# Print C compiler path
message(STATUS "*** C compiler path: " ${CMAKE_C_COMPILER} " ***")

include(cmake/Dependencies.cmake)