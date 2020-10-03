message(STATUS "*** Create Zinet Main Lib ***")

add_library(ZtMain ${ZINET_LIBS_TYPE}

	# Headers
	include/Zinet/Main/ZtMainConfig.h
	include/Zinet/Main/ZtLoggerBase.h
	include/Zinet/Main/ZtMainException.h
	
	# Source
	src/ZtLoggerBase.cpp
	src/ZtMainException.cpp
)

target_compile_features(ZtMain PUBLIC cxx_std_17)

set_target_properties(ZtMain PROPERTIES 
	LINKER_LANGUAGE CXX
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_library(Zinet::Main ALIAS ZtMain)

target_compile_definitions(ZtMain PUBLIC ZINET_MAIN_EXPORT)

set_target_properties( ZtMain
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)