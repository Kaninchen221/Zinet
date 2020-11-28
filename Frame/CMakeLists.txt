message(STATUS "*** Create Zinet Frame Lib ***")

add_library(ZtFrame ${ZINET_LIBS_TYPE}

	# Headers
	include/Zinet/Frame/ZtFrameConfig.h
	include/Zinet/Frame/ZtLoop.h
	include/Zinet/Frame/ZtFrameException.h
	include/Zinet/Frame/ZtLoopSettings.h
	include/Zinet/Frame/ZtEngine.h
	include/Zinet/Frame/ZtEngineSettings.h
	
	# Source
	src/ZtLoop.cpp
	src/ZtFrameException.cpp
	
)

target_compile_features(ZtFrame PUBLIC cxx_std_17)

set_target_properties(ZtFrame PROPERTIES 
	LINKER_LANGUAGE CXX
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_library(Zinet::Frame ALIAS ZtFrame)

target_compile_definitions(ZtFrame PUBLIC ZINET_FRAME_EXPORT)

set_target_properties( ZtFrame
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)