
add_executable(ZtFrame-tests
	main.cpp
	
	# Headers
	# Tests
	headers/ZtDummy-tests.h
	
	# Mocks
	
)

target_compile_features(ZtFrame-tests PUBLIC cxx_std_17)

target_compile_definitions(ZtFrame-tests PUBLIC GTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(ZtFrame-tests PRIVATE 
	headers/
	${ZT_CORE_INCLUDE_DIR}
	${ZT_FRAME_INCLUDE_DIR}
)

target_link_libraries(ZtFrame-tests ZtFrame gtest gmock)

set_target_properties( ZtFrame-tests
    PROPERTIES
	LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)