
message(STATUS "*** Fetch Box2D ***")

FetchContent_Declare(Box2D
  GIT_REPOSITORY https://github.com/erincatto/box2d.git
  GIT_TAG v2.4.0
)

FetchContent_MakeAvailable(Box2D)

set(BOX2D_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/box2d-src/include
)

set_target_properties( box2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)