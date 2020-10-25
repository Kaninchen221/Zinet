message(STATUS "*** Create Zinet Main Lib ***")

add_library(ZtMain ${ZINET_LIBS_TYPE}

	# Headers
	include/Zinet/Main/ZtMainConfig.h
	include/Zinet/Main/ZtMainException.h
	include/Zinet/Main/ZtLogger.h
	include/Zinet/Main/ZtClock.h
	include/Zinet/Main/ZtTime.h
	
	include/Zinet/Main/ECRS/ZtEntity.h
	include/Zinet/Main/ECRS/ZtSystemBase.h
	include/Zinet/Main/ECRS/ZtComponentBase.h
	include/Zinet/Main/ECRS/ZtResourceBase.h
	include/Zinet/Main/ECRS/ZtObject.h
	
	# Source
	src/ZtMainException.cpp
	src/ZtLogger.cpp
	src/ZtClock.cpp
	src/ZtTime.cpp
	src/ZtEntity.cpp
	src/ZtComponentBase.cpp
	src/ZtResourceBase.cpp
	src/ZtSystemBase.cpp
	src/ZtClock.cpp
	src/ZtTime.cpp
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