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

set_target_properties( ZtCore
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)