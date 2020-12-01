message(STATUS "*** Create Zinet Reflection Lib ***")

add_library(ZtReflection ${ZINET_LIBS_TYPE}

	# Headers
	include/Zinet/Reflection/ZtReflectionConfig.h
	include/Zinet/Reflection/ZtReflectionException.h
	
	# Source
	src/ZtReflectionException.cpp
	
)

target_compile_features(ZtReflection PUBLIC cxx_std_17)

set_target_properties(ZtReflection PROPERTIES 
	LINKER_LANGUAGE CXX
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_library(Zinet::Reflection ALIAS ZtReflection)

target_compile_definitions(ZtReflection PUBLIC ZINET_REFLECTION_EXPORT)

set_target_properties( ZtReflection
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)