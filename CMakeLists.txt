cmake_minimum_required(VERSION 3.20)

project(Zinet VERSION 0.1.2
                  DESCRIPTION "Game Engine"
                  LANGUAGES CXX)

# Usefull information
message(STATUS "*** CMakeList source dir : ${CMAKE_SOURCE_DIR} ***")
message(STATUS "*** C++ compiler path: ${CMAKE_CXX_COMPILER} ***")
message(STATUS "*** C compiler path: ${CMAKE_C_COMPILER} ***")

# Global compile options
add_compile_options()

# Global compile definitions
add_compile_definitions(ZINET_STATIC ZINET_WINDOWS)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Vulkan SDK
find_package(Vulkan REQUIRED FATAL_ERROR)

# Add subdirectories
add_subdirectory(Core)
add_subdirectory(GraphicLayer)
