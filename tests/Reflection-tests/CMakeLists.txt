
add_executable(ZtReflection-tests
	main.cpp
	
	# Headers
	# Tests
	headers/ZtReflectionException-tests.h
	headers/ZtReflectionRegister-tests.h
	
	# Mocks
	
)

target_compile_features(ZtReflection-tests PUBLIC cxx_std_17)

target_compile_definitions(ZtReflection-tests PUBLIC GTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(ZtReflection-tests PRIVATE 
	headers/
	${ZT_CORE_INCLUDE_DIR}
	${ZT_MAIN_INCLUDE_DIR}
	${ZT_REFLECTION_INCLUDE_DIR}
)

target_link_libraries(ZtReflection-tests ZtReflection gtest gmock)

set_target_properties( ZtReflection-tests
    PROPERTIES
	LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)