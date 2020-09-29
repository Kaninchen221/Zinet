cmake_minimum_required(VERSION 3.14)

include(FetchContent)

include(cmake/multiple_targets_compile_definitions.cmake)

project(Zinet VERSION 0.1
                  DESCRIPTION "Game Engine"
                  LANGUAGES CXX)

include(cmake/usefull_information.cmake)

include(cmake/zinet_libs_type_resolve.cmake)

include(cmake/dependencies.cmake)

add_executable(Sandbox main.cpp)

add_subdirectory(Core)
add_subdirectory(System)
 
set(ZINET_LIBS_NAME "Sandbox" "ZtCore" "ZtSystem")

include(cmake/os_platform_resolve.cmake)

include(cmake/propagate_include_dirs.cmake)

include(cmake/zinet_libs_include_directories.cmake)

include(cmake/zinet_libs_link_libraries.cmake)