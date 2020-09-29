cmake_minimum_required(VERSION 3.14)

include(FetchContent)

include(cmake/one_include_file.cmake)

project(Zinet VERSION 0.1
                  DESCRIPTION "Game Engine"
                  LANGUAGES CXX)

print_usefull_information()

zinet_libs_type_resolve()

fetch_dependencies()

add_executable(Sandbox main.cpp)

add_subdirectory(Core)
add_subdirectory(System)
 
set(ZINET_LIBS_NAME "Sandbox" "ZtCore" "ZtSystem")

os_platform_resolve()

propagate_include_dirs()

zinet_libs_include_directories()

zinet_libs_link_libraries()