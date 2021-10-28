cmake_minimum_required(VERSION 3.14)
				  
project(Zinet VERSION 0.1.2
                  DESCRIPTION "Game Engine"
                  LANGUAGES CXX)

# Usefull information
message(STATUS "*** CMakeList source dir : ${CMAKE_SOURCE_DIR} ***")
message(STATUS "*** C++ compiler path: ${CMAKE_CXX_COMPILER} ***")
message(STATUS "*** C compiler path: ${CMAKE_C_COMPILER} ***")

# Fetch dependencies 
# TODO: Template this to python
include(cmake/fetch_dependencies.cmake)

# Add subdirectories
add_subdirectory(Core)
add_subdirectory(Glad)
add_subdirectory(GraphicLayer)
add_subdirectory(EntryPoint)

# Should contains all libs and executables names
# Used for propagating macros to every target
# TODO: Make this propagation inside python
set(ZINET_TARGETS_NAMES "ZtEntryPoint" "ZtCore" "ZtCoreTest")

include(cmake/multiple_targets_compile_definitions.cmake) # Resolve problems with diffrent os

if(MSVC OR MSYS) # Windows
	
	message(STATUS "*** OS: Windows ***")
	# multiple_targets_compile_definitions("${ZINET_TARGETS_NAMES}" "ZINET_WINDOWS")
	
else()

	message(FATAL_ERROR "*** OS: NOT SUPPORTED ***")
	
endif()

set(ZINET_ENGINE_ROOT_PATH ZINET_ENGINE_ROOT_PATH="${CMAKE_SOURCE_DIR}")
multiple_targets_compile_definitions("${ZINET_TARGETS_NAMES}" ${ZINET_ENGINE_ROOT_PATH}) # Propagate macro with engine root folder