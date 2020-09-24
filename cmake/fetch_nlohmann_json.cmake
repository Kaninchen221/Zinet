
message(STATUS "*** Fetch Nlohmann Json ***")

FetchContent_Declare(Json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.9.1
)

FetchContent_MakeAvailable(Json)

# Create var contains PyBind11 include dir
set(SPDLOG_INCLUDE_DIRS PRIVATE 
	build/_deps/json-src/single_include
)