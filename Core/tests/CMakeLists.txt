message(STATUS "*** Create Zinet CoreTests executable ***")

add_executable(ZtCoreTests
	main.cpp
	
	# Header files
	include/ZtClockTests.h
	include/ZtTimeTests.h
	
)

target_compile_features(ZtCoreTests PUBLIC cxx_std_17)

set_target_properties(ZtCoreTests PROPERTIES LINKER_LANGUAGE CXX)
	
target_compile_definitions(ZtCoreTests PUBLIC GTEST_LINKED_AS_SHARED_LIBRARY)

set_target_properties(ZtCoreTests
    PROPERTIES
	LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)

target_include_directories(ZtCoreTests PRIVATE include/ ${ZT_CORE_INCLUDE_DIR})

target_link_libraries(ZtCoreTests ZtCore gtest gmock)