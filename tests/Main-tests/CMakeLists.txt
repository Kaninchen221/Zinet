
add_executable(ZtMain-tests
	main.cpp
	
	# Headers
	# Tests
	headers/ZtLogger-tests.h
	headers/ZtMainException-tests.h
	headers/ZtEntity-tests.h
	headers/ZtSystem-tests.h
	headers/ZtClock-tests.h
	headers/ZtTime-tests.h
	headers/ZtUniqueIndexer-tests.h
	headers/ZtIdentificator-tests.h
	headers/ZtComponentsManager-tests.h
	headers/ZtComponent-tests.h
	headers/ZtSystemsManager-tests.h
	
	# Mocks
	
)

target_compile_features(ZtMain-tests PUBLIC cxx_std_17)

target_compile_definitions(ZtMain-tests PUBLIC GTEST_LINKED_AS_SHARED_LIBRARY)

target_include_directories(ZtMain-tests PRIVATE 
	headers/
	${SPDLOG_INCLUDE_DIRS}
	${ZT_CORE_INCLUDE_DIR}
	${ZT_MAIN_INCLUDE_DIR}
	${COLONY_INCLUDE_DIRS}
)

target_link_libraries(ZtMain-tests ZtMain gtest gmock spdlog)

set_target_properties( ZtMain-tests
    PROPERTIES
	LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)