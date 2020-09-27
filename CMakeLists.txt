cmake_minimum_required(VERSION 3.14)

include(FetchContent)

include(cmake/multiple_targets_compile_definitions.cmake)

project(Zinet VERSION 0.1
                  DESCRIPTION "Game Engine"
                  LANGUAGES CXX)

message(STATUS "*** CMakeList source dir : ${CMAKE_SOURCE_DIR} ***")
message(STATUS "*** C++ compiler path: ${CMAKE_CXX_COMPILER} ***")
message(STATUS "*** C compiler path: ${CMAKE_C_COMPILER} ***")

include(cmake/zinet_libs_type_resolve.cmake)

include(cmake/Dependencies.cmake)

add_executable(Sandbox main.cpp)

add_subdirectory(Core)
add_subdirectory(System)
 
set(ZINET_LIBS_NAME "Sandbox" "ZtCore" "ZtSystem")

include(cmake/os_platform_resolve.cmake)

get_property(ZT_CORE_INCLUDE_DIR TARGET ZtCore PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
get_property(ZT_SYSTEM_INCLUDE_DIR TARGET ZtSystem PROPERTY INCLUDE_DIRECTORIES)

message(STATUS "*** ZtCore include path: ${ZT_CORE_INCLUDE_DIR} ***")
message(STATUS "*** ZtSystem include path: ${ZT_SYSTEM_INCLUDE_DIR} ***")

target_include_directories(Sandbox PRIVATE ${ZT_CORE_INCLUDE_DIR})
target_include_directories(Sandbox PRIVATE ${ZT_SYSTEM_INCLUDE_DIR})
target_include_directories(ZtSystem PRIVATE ${ZT_CORE_INCLUDE_DIR})