
message(STATUS "*** Fetch STB ***")

FetchContent_Declare(STB
  GIT_REPOSITORY https://github.com/nothings/stb.git
)

FetchContent_MakeAvailable(STB)

set(STB_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/stb-src
)