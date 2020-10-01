
add_executable(ZtSystem-tests
	main.cpp
)

target_link_libraries(ZtSystem-tests ZtSystem gtest gmock)

set_target_properties( ZtSystem-tests
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)