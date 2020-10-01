
add_executable(ZtMain-tests
	main.cpp
	
	# Headers
	ZtLogger-tests.h
)

target_include_directories(ZtMain-tests PRIVATE 
	${SPDLOG_INCLUDE_DIRS}
	${ZT_CORE_INCLUDE_DIR}
	${ZT_MAIN_INCLUDE_DIR}
)

target_link_libraries(ZtMain-tests ZtMain gtest gmock spdlog)

set_target_properties( ZtMain-tests
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)