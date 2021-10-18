
message(STATUS "*** Fetch GLM ***")

FetchContent_Declare(GLM
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.8
)

FetchContent_MakeAvailable(GLM)

set(GLM_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/glm-src/glm
)

set_target_properties(glm
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)