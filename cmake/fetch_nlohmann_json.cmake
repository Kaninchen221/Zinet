
message(STATUS "*** Fetch Nlohmann Json ***")

FetchContent_Declare(Json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.9.1
)

FetchContent_MakeAvailable(Json)

set(JSON_INCLUDE_DIRS PRIVATE 
	${CMAKE_BINARY_DIR}/_deps/json-src/single_include
)