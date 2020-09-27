message(STATUS "*** Create Zinet Core Lib ***")

add_library(ZtCore OBJECT
	include/Zinet/Core/ZtCore.h
)

set_target_properties(ZtCore PROPERTIES 
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_library(Zinet::Core ALIAS ZtCore)