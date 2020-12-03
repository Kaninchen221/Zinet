
message(STATUS "*** Fetch Colony ***")

FetchContent_Declare( colony
  GIT_REPOSITORY https://github.com/mattreecebentley/plf_colony.git
  GIT_TAG master
)

FetchContent_MakeAvailable(colony)

set(COLONY_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/colony-src
)