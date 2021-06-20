cmake_minimum_required(VERSION 3.14)

# Create project
project(Zinet VERSION 0.1.1
                  DESCRIPTION "Game Engine"
                  LANGUAGES CXX)

# Usefull information
message(STATUS "*** CMakeList source dir : ${CMAKE_SOURCE_DIR} ***")
message(STATUS "*** C++ compiler path: ${CMAKE_CXX_COMPILER} ***")
message(STATUS "*** C compiler path: ${CMAKE_C_COMPILER} ***")

# Check Zinet libs type
set(ZINET_LIBS_TYPE "SHARED" CACHE STRING "Must be SHARED or STATIC")

if(${ZINET_LIBS_TYPE} STREQUAL "SHARED" OR ${ZINET_LIBS_TYPE} STREQUAL "STATIC")
	message(STATUS "*** Zinet Libs Type : ${ZINET_LIBS_TYPE} ***")
else()
	message(FATAL_ERROR "*** INVALID Zinet Libs Type : ${ZINET_LIBS_TYPE} ***")
endif()

# Fetch dependencies
include(cmake/fetch_dependencies.cmake)

# Add Zinet libs
add_subdirectory(Core)

# Zinet EntryPoint executable program
add_subdirectory(EntryPoint)

# Should contains all libs and executables names
set(ZINET_TARGETS_NAMES "ZtEntryPoint" "ZtCore" "ZtCoreTests")

# Resolve problems with diffrent os
include(cmake/multiple_targets_compile_definitions.cmake)

if(MSVC OR MSYS) # Windows
	
	message(STATUS "*** OS: Windows ***")
	multiple_targets_compile_definitions("${ZINET_TARGETS_NAMES}" "ZINET_WINDOWS")
	
else()

	message(FATAL_ERROR "*** OS: NOT SUPPORTED ***")
	
endif()

# Propagate macro with engine root folder
set(ZINET_ENGINE_ROOT_PATH ZINET_ENGINE_ROOT_PATH="${CMAKE_SOURCE_DIR}")
multiple_targets_compile_definitions("${ZINET_TARGETS_NAMES}" ${ZINET_ENGINE_ROOT_PATH})