message(STATUS "*** Create Zinet EntryPoint program ***")

add_executable(ZtEntryPoint
	
	# Header files
	
	# Source files
	source/main.cpp
	
)

target_compile_features(ZtEntryPoint PUBLIC cxx_std_17)

set_target_properties(ZtEntryPoint PROPERTIES 
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(ZtEntryPoint
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)

target_include_directories(ZtEntryPoint PRIVATE ${ZT_CORE_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS})

target_link_libraries(ZtEntryPoint PRIVATE ZtCore sfml-graphics sfml-system sfml-window sfml-audio)