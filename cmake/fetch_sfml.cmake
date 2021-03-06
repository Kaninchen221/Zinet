
message(STATUS "*** Fetch SFML ***")

FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.5.1
)

FetchContent_MakeAvailable(SFML)

set(SFML_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/sfml-src/include
)

set_target_properties( 
	sfml-audio 
	sfml-graphics 
	sfml-network 
	sfml-system 
	sfml-window
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)