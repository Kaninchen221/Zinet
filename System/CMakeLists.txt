message(STATUS "*** Create Zinet System Lib ***")

add_library(ZtSystem ${ZINET_LIBS_TYPE}

	# Headers
	include/Zinet/System/ZtSystemConfig.h
	include/Zinet/System/ZtSystemInterface.h
	
	# Source
	src/ZtSystemInterface.cpp
)

target_compile_features(ZtSystem PUBLIC cxx_std_17)

set_target_properties(ZtSystem PROPERTIES 
	LINKER_LANGUAGE CXX
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_library(Zinet::System ALIAS ZtSystem)

target_compile_definitions(ZtSystem PUBLIC ZINET_SYSTEM_EXPORT)

set_target_properties( ZtSystem
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)