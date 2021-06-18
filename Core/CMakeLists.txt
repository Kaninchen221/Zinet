message(STATUS "*** Create Zinet Core Lib ***")

add_library(ZtCore SHARED ${ZINET_LIBS_TYPE}
	
	# Header files
	include/Zinet/Core/ZtCore.h
	include/Zinet/Core/ZtLoop.h
	include/Zinet/Core/ZtClock.h
	include/Zinet/Core/ZtTime.h
	
	# Source files
	source/ZtLoop.cpp
	source/ZtClock.cpp
	source/ZtTime.cpp
)

target_compile_features(ZtCore PUBLIC cxx_std_17)

set_target_properties(ZtCore PROPERTIES 
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_library(Zinet::Core ALIAS ZtCore)

set_target_properties(ZtCore
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)

target_include_directories(ZtCore PRIVATE ${SFML_INCLUDE_DIRS})

target_link_libraries(ZtCore PRIVATE sfml-system sfml-window sfml-audio)
target_link_libraries(ZtCore PRIVATE ImGui-SFML::ImGui-SFML)

# Propagate include dirs
get_property(ZT_CORE_INCLUDE_DIRS_TEMP TARGET ZtCore PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
set(ZT_CORE_INCLUDE_DIRS ${ZT_CORE_INCLUDE_DIRS_TEMP} PARENT_SCOPE)
message(STATUS "*** ZtCore include path: ${ZT_CORE_INCLUDE_DIRS} ***")

# Tests
add_subdirectory(tests)