
message(STATUS "*** Fetch SPDLOG ***")

FetchContent_Declare(SPDLOG
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.5.0
)

FetchContent_MakeAvailable(SPDLOG)
# Create var contains SPDLOG include dir
set(SPDLOG_INCLUDE_DIRS PRIVATE 
	build/_deps/spdlog-src/include
)
