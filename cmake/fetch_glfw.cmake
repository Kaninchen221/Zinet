
message(STATUS "*** Fetch GLFW ***")

FetchContent_Declare(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.4
)

FetchContent_MakeAvailable(glfw)

set(GLFW_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/glfw-src/include
)

set_target_properties(glfw
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)