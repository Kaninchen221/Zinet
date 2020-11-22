
add_executable(ZtFrame-tests
	main.cpp
	
	# Headers
	# Tests
	headers/ZtLoop-tests.h
	headers/ZtFrameException-tests.h
	
	# Mocks
	
)

target_compile_features(ZtFrame-tests PUBLIC cxx_std_17)

target_compile_definitions(ZtFrame-tests PUBLIC GTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(ZtFrame-tests PRIVATE 
	headers/
	${ZT_CORE_INCLUDE_DIR}
	${ZT_MAIN_INCLUDE_DIR}
	${ZT_FRAME_INCLUDE_DIR}
	${SFML_INCLUDE_DIRS}
)

target_link_libraries(ZtFrame-tests ZtFrame gtest gmock sfml-graphics sfml-window sfml-system sfml-audio)

set_target_properties( ZtFrame-tests
    PROPERTIES
	LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)